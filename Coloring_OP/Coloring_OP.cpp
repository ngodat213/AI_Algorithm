#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const int SIZE = 99;

int viTri(int a[])
{
    int max = 0;
    for(int i = 1; i < 8; i++)
    {
        if(a[max] < a[i])
            max = i;
    }
    return max;
}

void readGraph(int a[SIZE][SIZE], int bac[SIZE], int& sizeArr) {
    ifstream inputFile("input.txt");
    inputFile >> sizeArr;

    for (int i = 0; i < sizeArr; i++) {
        for (int j = 0; j < sizeArr; j++) {
            inputFile >> a[i][j];
        }
        bac[i] = 0;
    }
    inputFile.close();
}

void writeOutputToFile(int toMau[SIZE], int size) {
    ofstream outputFile("output.txt");
    vector<vector<char>> colors(size);

    for (int i = 0; i < size; ++i) {
        char color = 'A' + toMau[i];
        colors[toMau[i]].push_back('A' + i);
    }

    for (int i = 0; i < size; ++i) {
        if (!colors[i].empty()) {
            outputFile << "Mau" << i + 1 << ": ";
            for (char vertex : colors[i]) {
                outputFile << vertex << " ";
            }
            outputFile << endl;
        }
    }

    outputFile.close();
}

int main()
{

    int toMau[SIZE] = {-1}, bac[SIZE] = {0}, sizeArr;
    int cam[SIZE][SIZE] = {-1};
    int a[SIZE][SIZE];

    readGraph(a, bac, sizeArr);

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            bac[i] += a[i][j];
            cam[i][j] = -1;
        }
        toMau[i] = -1;
    }

    while(bac[viTri(bac)] > 0){
        int maxArr = viTri(bac);
        int daTo;
        //TO MAU
        for(int i = 0; i < 8; i++){
            if(cam[maxArr][i] == -1){
                toMau[maxArr] = i;
                daTo = i;
                break;
            }
        }
        // SET 0
        bac[maxArr] = 0;
        // HA BAC && CAM TO
        for(int i = 0; i < 8; i++){
            // Kiem tra quan he
            if(a[maxArr][i] != 0 && i != maxArr){
                cam[i][daTo] = daTo;
                if(bac[i] != 0){
                    bac[i] -= 1;
                }
            }
        }
    }
    // TO MAU CON THIEU
    for(int i = 0; i < 8; i++){
        if(toMau[i] == -1){
            for(int j = 0; j < 8; j++){
                if(cam[i][j] == -1){
                    toMau[i] = j;
                    break;
                }
            }

        }
    }

    writeOutputToFile(toMau, sizeArr);

    return 0;
}
