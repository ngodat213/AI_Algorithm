#include <iostream>
#include <vector>
#include <stack>
#include <fstream>

using namespace std;

const int SIZE = 99;

void readGraph(int a[SIZE][SIZE], int& n, int &start, int &end) {
    ifstream inputFile("input.txt");
    inputFile >> n >> start >> end;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inputFile >> a[i][j];
        }
    }
    inputFile.close();
}

void DFS(int graph[SIZE][SIZE], int start, int end, int n) {
    ofstream outputFile("output.txt");

    vector<bool> visited(n, false);
    vector<int> father(n, -1);
    stack<int> L;
    L.push(start);
    visited[start] = true;

    while (!L.empty()) {
        int s = L.top();
        L.pop();

        if (s == end) {
            outputFile << "Path: ";
            while (s != -1) {
                outputFile << s << " ";
                s = father[s];
            }
            outputFile << endl;
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (graph[s][i] && !visited[i]) {
                L.push(i);
                visited[i] = true;
                father[i] = s;
            }
        }
    }
    outputFile << "FAILURE";
}

int main() {
    int a[SIZE][SIZE], n, START, GOAL;
    readGraph(a, n, START, GOAL);
    DFS(a, START, GOAL, n);
    return 0;
}
