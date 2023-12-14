#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

const int SIZE = 99;
const int INF = 1e9;

void readGraph(int a[SIZE][SIZE], int h[SIZE], int& sizeArr, int &start, int &end) {
    ifstream inputFile("input.txt");
    inputFile >> sizeArr >> start >> end;

    for (int i = 0; i < sizeArr; i++) {
        for (int j = 0; j < sizeArr; j++) {
            inputFile >> a[i][j];
        }
    }
    for (int i = 0; i < sizeArr; i++) {
        inputFile >> h[i];
    }
    inputFile.close();
}

void AT(int graph[SIZE][SIZE], int h[SIZE], int START, int GOAL, int n){
    ofstream outputFile("output.txt");

    vector<int> prev(n, -1);
    vector<int> g(SIZE, INF), f(SIZE, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({START, {START}});
    g[START] = 0;
    f[START] = h[START] + h[START];

    while (!pq.empty()) {
        int s = pq.top().second;
        pq.pop();

        for (int i = 0; i < n; ++i) {
            if (graph[s][i] && g[s] + graph[s][i] < g[i]) {
                g[i] = g[s] + graph[s][i];
                f[i] = g[i] + h[i];
                prev[i] = s;
                pq.push({f[i], i});
            }
        }

         // kiểm tra dích và in
        if (s == GOAL) {
            // quay lùi 
            vector<int> path;
            for (int s = GOAL; s != -1; s = prev[s]) {
                path.push_back(s);
            }

            outputFile << "Path: ";
            for (int i = path.size() - 1; i >= 0; --i) {
                outputFile << path[i] << " ";
            }
            outputFile << "\nCost: " << g[GOAL] << endl;
            return;
        }
    }
    outputFile << "FAILURE";
}

int main()
{
    int a[SIZE][SIZE], h[SIZE], n, START, GOAL;
    readGraph(a, h, n, START, GOAL);
    AT(a, h, START, GOAL, n);
    return 0;
}
