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

    vector<vector<int>> C(n1, vector<int>(m2, 0));

    auto inicio = chrono::high_resolution_clock::now();

    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m2; j++) {
            for(int k = 0; k < m1; k++) {
                C[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo = fim - inicio;

    ofstream saida("resultado_sequencial.txt");
    saida << n1 << " " << m2 << "\n";
    
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m2; j++) {
            saida << "c" << i+1 << j+1 << " " << C[i][j] << "\n";
        }
    }
    
    saida << tempo.count() << "\n";
    saida.close();

    cout << "Tempo do sequencial: " << tempo.count() << " segundos" << endl;

    return 0;
}