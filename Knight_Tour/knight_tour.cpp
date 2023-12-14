#include<iostream>
#include<fstream>
#define MAX 8
using namespace std;

int A[MAX][MAX] = { 0 }; // Initialize array with value 0
int X[8] = { -2,-2,-1,-1, 1, 1, 2, 2 };
int Y[8] = { -1, 1,-2, 2,-2, 2,-1, 1 };
int dem = 0; // Number of moves
int n;

void xuat(ofstream& outfile) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            outfile << A[i][j] << " ";
        outfile << endl;
    }
    outfile << endl;
}

void diChuyen(int x, int y, ofstream& outfile) {
    ++dem; // Increment move count
    A[x][y] = dem; // Mark as visited
    for (int i = 0; i < 8; i++) {
        // Check if the knight has visited all squares
        if (dem == n * n) {
            outfile << "Cac buoc di la: \n";
            xuat(outfile);
            exit(0);
        }
        // If not, create a new move
        int u = x + X[i]; // New x position
        int v = y + Y[i]; // New y position
        // If valid move, proceed with the move
        if (u >= 0 && u < n && v >= 0 && v < n && A[u][v] == 0)
            diChuyen(u, v, outfile);
    }
    // If no move is found, revert the changes
    --dem;
    A[x][y] = 0;
}

int main() {
    ifstream infile("input.txt"); // Assuming input is in "input.txt"
    ofstream outfile("output.txt"); // Output will be written to "output.txt"
    
    if (!infile.is_open() || !outfile.is_open()) {
        cerr << "Error opening files." << endl;
        return 1;
    }

    infile >> n;
    int a, b;
    infile >> a;
    infile >> b;

    diChuyen(a, b, outfile);

    // If no solution is found, print a message
    outfile << "Khong tim thay duong di.";

    // Close the files
    infile.close();
    outfile.close();

    return 0;
}
