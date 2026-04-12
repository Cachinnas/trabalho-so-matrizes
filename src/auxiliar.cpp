#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

// Função para gerar matriz e salvar no arquivo
void gerarMatriz(string nomeArquivo, int linhas, int colunas) {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro ao criar " << nomeArquivo << endl;
        return;
    }

    arquivo << linhas << " " << colunas << "\n";
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            arquivo << rand() % 100 << " "; // Valores entre 0 e 99
        }
        arquivo << "\n";
    }
    arquivo.close();
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        cout << "Uso: ./aux <n1> <m1> <n2> <m2>\n";
        return 1;
    }

    int n1 = stoi(argv[1]);
    int m1 = stoi(argv[2]);
    int n2 = stoi(argv[3]);
    int m2 = stoi(argv[4]);

    if (m1 != n2) {
        cout << "Erro: O numero de colunas da M1 deve ser igual ao de linhas da M2.\n";
        return 1;
    }

    srand(time(NULL)); // Semente para os números aleatórios

    gerarMatriz("M1.txt", n1, m1);
    gerarMatriz("M2.txt", n2, m2);

    cout << "Matrizes M1 e M2 geradas com sucesso.\n";
    return 0;
}