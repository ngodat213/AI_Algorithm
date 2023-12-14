#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <string>

using namespace std;

const int SIZE = 99;

void readGraph(int a[SIZE][SIZE], int& sizeArr, int &start) {
    ifstream inputFile("input.txt");
    inputFile >> sizeArr >> start;

    for (int i = 0; i < sizeArr; i++) {
        for (int j = 0; j < sizeArr; j++) {
            inputFile >> a[i][j];
        }
    }
    inputFile.close();
}

void GTS1(int a[SIZE][SIZE], int n, int s) {
    ofstream outputFile("output.txt");
    vector<int> tour;
    vector<bool> visited(n, false);

    int v = s;
    int cost = 0;
    tour.push_back(v);
    visited[v] = true;

    for (int i = 0; i < n - 1; ++i) {
        int w = -1;
        int minCost = INT_MAX;

        for (int j = 0; j < n; ++j) {
            if (!visited[j] && a[v][j] < minCost) {
                w = j;
                minCost = a[v][j];
            }
        }

        v = w;
        cost += minCost;
        tour.push_back(v);
        visited[v] = true;
    }

    cost += a[v][tour[0]];
    tour.push_back(tour[0]);

    outputFile << "Tour: {";
    for (int i = 0; i < tour.size() - 1; ++i) {
        outputFile << "(" << tour[i] << "," << tour[i + 1] << ") ";
    }
    outputFile << "}" << endl;

    outputFile << "Cost: " << cost << endl;
}

int main() {
    int graph[SIZE][SIZE], n, START; 
    readGraph(graph, n, START);
    GTS1(graph, n, START);
    return 0;
}
