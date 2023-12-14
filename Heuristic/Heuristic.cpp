#include <iostream>
#include <vector>
#include<fstream>
#include <algorithm>

using namespace std;

void printAssignment(const vector<vector<int>>& assignment) {
    ofstream outfile("output.txt"); // Output will be written to "output.txt"
    for (int i = 0; i < assignment.size(); ++i) {
        outfile << "Nguoi " << i + 1 << ": ";
        for (int j = 0; j < assignment[i].size(); ++j) {
            outfile << assignment[i][j] + 1;
            if (j < assignment[i].size() - 1) {
                outfile << ", ";
            }
        }
        outfile << endl;
    }
}

void greedyAssignment(const vector<vector<int>>& tij, int m, int n) {
    vector<vector<int>> assignment(m); // Lưu phân công công việc cho từng người
    vector<int> time(m, 0); // Lưu thời gian hoàn thành của mỗi người

    for (int j = 0; j < n; ++j) {
        int minTime = INT_MAX;
        int minPerson = -1;
        // Tìm người có thời gian hoàn thành nhỏ nhất cho công việc j
        for (int i = 0; i < m; ++i) {
            if (time[i] + tij[i][j] < minTime) {
                minTime = time[i] + tij[i][j];
                minPerson = i;
            }
        }
        // Phân công công việc j cho người có thời gian hoàn thành nhỏ nhất
        assignment[minPerson].push_back(j);
        time[minPerson] = minTime;
    }
    // In kết quả
    printAssignment(assignment);
}

int main() {
     ifstream infile("input.txt");
    if (!infile.is_open()) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int n, m;
    infile >> n >> m;

    vector<vector<int>> tij(m, vector<int>(n));
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            infile >> tij[i][j];
        }
    }

    infile.close();
    // Áp dụng thuật toán Greedy
    greedyAssignment(tij, m, n);

    return 0;
}
