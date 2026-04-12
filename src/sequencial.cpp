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

    // Lendo o arquivo 1 direto na main
    ifstream arq1(argv[1]);
    arq1 >> n1 >> m1;
    
    vector<vector<int>> M1(n1, vector<int>(m1));
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < m1; j++) {
            arq1 >> M1[i][j];
        }
    }
    arq1.close();

    // Lendo o arquivo 2 direto na main
    ifstream arq2(argv[2]);
    arq2 >> n2 >> m2;

    vector<vector<int>> M2(n2, vector<int>(m2));
    for (int i = 0; i < n2; i++) {
        for (int j = 0; j < m2; j++) {
            arq2 >> M2[i][j];
        }
    }
    arq2.close();

    // Prepara a matriz C cheia de zeros
    vector<vector<int>> C(n1, vector<int>(m2, 0));

    // Começa a contar o tempo
    auto inicio = chrono::high_resolution_clock::now();

    // Multiplicação bruta
    for(int i = 0; i < n1; i++) {
        for(int j = 0; j < m2; j++) {
            for(int k = 0; k < m1; k++) {
                C[i][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    // Para de contar
    auto fim = chrono::high_resolution_clock::now();
    chrono::duration<double> tempo = fim - inicio;

    // Gerando o arquivo de saida
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