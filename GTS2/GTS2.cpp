#include <iostream>
#include <vector>
#include <climits>
#include <fstream>

using namespace std;

const int SIZE = 6;

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

void GTS1(int a[SIZE][SIZE], int n, int s, int &minCost, vector<int> &minTour) {
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

    if (cost < minCost) {
        minCost = cost;
        minTour = tour;
    }
}

void GTS2(int graph[SIZE][SIZE],int n){
    ofstream outputFile("output.txt");
    vector<int> minTour;
    int minCost = 1e9;

    for (int startCity = 0; startCity < n; ++startCity) {
        GTS1(graph, n, startCity, minCost, minTour);
    }

    outputFile << "Tour: {";
    for (int i = 0; i < minTour.size() - 1; ++i) {
        outputFile << "(" << minTour[i] << "," << minTour[i + 1] << ") ";
    }
    outputFile << "}" << endl;

    outputFile << "Cost: " << minCost << endl;
}

int main() {
    int graph[SIZE][SIZE], n; 
    readGraph(graph, n);
    GTS2(graph, n);
    return 0;
}
