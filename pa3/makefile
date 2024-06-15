CXX = g++
CXXFLAGS = -std=c++17 -O3

SRCS = src/cb.cpp src/graph.cpp src/disjoint_set.cpp
BIN_DIR = bin
TARGET = $(BIN_DIR)/cb

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY: all clean
