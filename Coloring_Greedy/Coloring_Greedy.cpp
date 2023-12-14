#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int SIZE = 99;


void readGraph(int a[SIZE][SIZE], int& sizeArr) {
    ifstream inputFile("input.txt");
    inputFile >> sizeArr;

    for (int i = 0; i < sizeArr; i++) {
        for (int j = 0; j < sizeArr; j++) {
            inputFile >> a[i][j];
        }
    }
    inputFile.close();
}


void Coloring_Greedy(int graph[SIZE][SIZE], int n) {
    ofstream outputFile("output.txt");
    vector<int> color(SIZE, -1);

    for (int v = 0; v < SIZE; ++v) {
        vector<bool> availableColors(SIZE, true);

        // Kiểm tra màu của các đỉnh kề và đánh dấu màu đã được sử dụng
        for (int i = 0; i < SIZE; ++i) {
            if (graph[v][i] && color[i] != -1) {
                availableColors[color[i]] = false;
            }
        }

        // Tìm màu đầu tiên có thể sử dụng
        for (int c = 0; c <= SIZE; ++c) {
            if (availableColors[c]) {
                color[v] = c;
                break;
            }
        }
    }

    // In màu
    outputFile << "Đỉnh\tMàu" << endl;
    for (int i = 0; i < n; ++i) {
        outputFile << i << "\t\t" << color[i] << endl;
    }
}

int main() {
    int graph[SIZE][SIZE], n;
    readGraph(graph, n);
    Coloring_Greedy(graph, n);

    return 0;
}
