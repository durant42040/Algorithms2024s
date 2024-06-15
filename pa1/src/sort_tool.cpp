// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2020/9/15 Mu-Ting Wu]
//  Modify     [2023/9/12 Ming-Bang Fan]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>
#include <random>
#include <limits>

using namespace std;

#define ll long long

// Constructor
SortTool::SortTool() {}

// Insertion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    for(int i=1; i < data.size(); ++i) {
        int j = i-1;
        int key = data[i];
        while(j >= 0 && data[j] > key) {
            data[j+1] = data[j];
            j--;
        };
        data[j + 1] = key;
    }
}

// Quick sort method
void SortTool::QuickSort(vector<int>& data, int f){
    static random_device rd;
    static mt19937 gen(rd());
    QuickSortSubVector(data, 0, data.size() - 1, f, gen);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high, const int flag, mt19937& gen) {
    // Function : Quick sort subvector
    // flag == 0 -> normal QS
    // flag == 1 -> randomized QS
    if(low < high) {
        int pivot = flag == 1? RandomizedPartition(data, low, high, gen) : Partition(data, low, high);
        QuickSortSubVector(data, low, pivot-1, flag, gen);
        QuickSortSubVector(data, pivot+1, high, flag, gen);
    }
}

int SortTool::RandomizedPartition(vector<int>& data, int low, int high, mt19937& gen){
    // Function : RQS's Partition the vector 
    uniform_int_distribution<> distrib(low, high);
    int i = distrib(gen);

    int temp = data[i];
    data[i] = data[high];
    data[high] = temp;

    return Partition(data, low, high);
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector
    int pivot = data[high];
    int i = low - 1;
    for(int j=low; j<high; ++j) {
        if(data[j] < pivot) {
            i++;
            int temp = data[i];
            data[i] = data[j];
            data[j] = temp;
        }
    }
    int temp = data[i+1];
    data[i+1] = data[high];
    data[high] = temp;
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    if(low < high) {
        int mid = (low + high)/2;
        MergeSortSubVector(data, low, mid);
        MergeSortSubVector(data, mid+1, high);
        Merge(data, low, mid, high);
    }
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int mid, int high) {
    // Function : Merge two sorted subvector
    int n1 = mid - low + 1;
    int n2 = high - mid;

    int* left = new int[n1+1];
    int* right = new int[n2+1];

    for(int i = 0; i < n1; ++i) {
        left[i] = data[low + i];
    }
    left[n1] = numeric_limits<int>::max();

    for(int i = 0; i < n2; ++i) {
        right[i] = data[mid + i + 1];
    }
    right[n2] = numeric_limits<int>::max();

    int i = 0;
    int j = 0;
    for(int k = low; k <= high; ++k) {
        if(left[i] < right[j]) {
            data[k] = left[i];
            i++;
        } else {
            data[k] = right[j];
            j++;
        }
    }

    delete[] left;
    delete[] right;
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    int left = 2*root + 1;
    int right = 2*root + 2;
    int largest = root;
    if(left < heapSize && data[left] > data[largest]) {
        largest = left;
    }
    if(right < heapSize && data[right] > data[largest]) {
        largest = right;
    }
    if(largest != root) {
        swap(data[root], data[largest]);
        MaxHeapify(data, largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    for(int i = heapSize/2; i >= 0; --i) {
        MaxHeapify(data, i);
    }
}
