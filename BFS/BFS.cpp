#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

const int SIZE = 99;

void readGraph(int a[SIZE][SIZE], int& sizeArr, int &start, int &end) {
    ifstream inputFile("input.txt");
    inputFile >> sizeArr >> start >> end;

    for (int i = 0; i < sizeArr; i++) {
        for (int j = 0; j < sizeArr; j++) {
            inputFile >> a[i][j];
        }
    }
    inputFile.close();
}

void AT(int graph[SIZE][SIZE], int START, int GOAL, int n){
    ofstream outputFile("output.txt");

    vector<bool> visited(n, 0);
    queue<pair<int, vector<int>>> prev;

    prev.push({START, {START}});
    visited[START] = 1;

    while (!prev.empty()) {
        int s = prev.front().first;
        vector<int> path = prev.front().second;
        prev.pop();
        // check goal
        if (s == GOAL) {
            outputFile << "Path: ";
            for (int node : path) {
                outputFile << node << " ";
            }
            return;
        }

        // -------print succs------- //
        queue<pair<int, vector<int>>> pv = prev;
        outputFile << s << " -> ";
        outputFile << "succs={";
        while (!pv.empty()) {
   		  outputFile << pv.front().first <<"-"; 
  		  pv.pop();
        }
        outputFile << "}" << endl;
        // ------------------------- //
        
        for (int i = 0; i < n; ++i) {
            if (graph[s][i] && !visited[i]) {
                visited[i] = 1;
                vector<int> newPrev = path; // lưu prev
                newPrev.push_back(i);
                prev.push({i, newPrev});
            }
        }
    }
    outputFile << "FAIL";
}

int main()
{
    int a[SIZE][SIZE], n, START, GOAL;
    readGraph(a, n, START, GOAL);
    AT(a, START, GOAL, n);
    return 0;
}
