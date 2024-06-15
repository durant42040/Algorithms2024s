#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

const string prefix = "/raid4/courses/alg2024s/alg24s104/b11901040_pa2/";
string in_path = "inputs/12.in";
string ou_path = "outputs/12.out";

map<pair<int, int>, vector<pair<int, int>>> memo;

vector<pair<int, int>> maximum_planar_subset(int i, int j, vector<vector<int>>& endpoint, vector<int>& table) {
    if (memo.count({i, j})) return memo[{i, j}];

    vector<pair<int, int>> mps;
    vector<pair<int, int>> mps_2;
    if(i == j) {
        return {};
    }
    switch (endpoint[i][j]) {
        case 1:
            mps = maximum_planar_subset(i, j-1, endpoint, table);
            break;
        case 2:
            mps = maximum_planar_subset(i, table[j]-1, endpoint, table);
            mps_2 = maximum_planar_subset(table[j]+1, j, endpoint, table);
            mps.push_back(make_pair(table[j], j));
            mps.insert(mps.end(), mps_2.begin(), mps_2.end());
            break;
        default:
            return {};
    }
    memo[{i, j}] = mps;
    return mps;
}

int main (int argc, const char* argv[]) {
    ifstream ifs;
    if(argc > 1) in_path = argv[1];
    if(argc > 2) ou_path = argv[2];
    ifs.open(prefix+in_path);

    if(!ifs.is_open()) {
        cout << "failed to open file.\n";
        return 1;
    }

    int buf1, buf2;
    ifs >> buf1;
    const int N(buf1);

    vector<int> table(N,0);
    for(int i=0; i<N/2; i++) {
        ifs >> buf1 >> buf2;
        table[buf1] = buf2;
        table[buf2] = buf1;
    }

    ifs.close();

    vector<vector<int>> dp(N, vector<int>(N, 0));
    vector<vector<int>> endpoint(N, vector<int>(N, 0));

    for(int j = 0; j < N; j++) {
        int k = table[j];
        for(int i = 0; i < j; i++) {
            if(k > j || k < i) {
                dp[i][j] = dp[i][j - 1];
                endpoint[i][j] = 1;
            } else {
                int dp_1 = dp[i][j - 1];
                int dp_2 = dp[i][k - 1] + dp[k + 1][j - 1] + 1;

                if (dp_1 >= dp_2) {
                    dp[i][j] = dp_1;
                    endpoint[i][j] = 1;
                } else {
                    dp[i][j] = dp_2;
                    endpoint[i][j] = 2;
                }
            }
        }
    }

    vector<pair<int, int>> mps = maximum_planar_subset(0, N-1, endpoint, table);


    ofstream ofs;
    ofs.open(prefix + ou_path);
    if(!ofs.is_open()) {
        cout << "Failed to open file.\n";
        return 1;
    }

    ofs << dp[0][N-1] << endl;
    for (const auto& p : mps) {
        ofs << p.first << " " << p.second << endl;
    }
}