#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 3) {
        cout << "Erro: precisa passar os dois txts das matrizes." << endl;
        return 1;
    }

    int n1, m1, n2, m2;

    ifstream arq1(argv[1]);
    arq1 >> n1 >> m1;
    
    vector<vector<int>> M1(n1, vector<int>(m1));
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            arq1 >> M1[i][j];
        }
    }
    arq1.close();
    
    ifstream arq2(argv[2]);
    arq2 >> n2 >> m2;

    vector<vector<int>> M2(n2, vector<int>(m2));
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            arq2 >> M2[i][j];
        }
    }
    arq2.close();