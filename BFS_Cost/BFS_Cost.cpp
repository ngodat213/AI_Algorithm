#include <iostream>
#include <queue>
#include <vector>
#include <fstream>
using namespace std;

const int SIZE = 99;
const int INF = 1e9;

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

    vector<int> prev(n, -1);
    vector<int> g(SIZE, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    pq.push({START, {START}});
    g[START] = 0;

    while (!pq.empty()) {
        int cost = pq.top().first;
        int s = pq.top().second;
        pq.pop();

        for (int i = 0; i < n; ++i) {
            if (graph[s][i] && cost + graph[s][i] < g[i]) {
                g[i] = cost + graph[s][i];
                prev[i] = s;
                pq.push({g[i], i});
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
    int a[SIZE][SIZE], n, START, GOAL;
    readGraph(a, n, START, GOAL);
    AT(a, START, GOAL, n);
    return 0;
}
