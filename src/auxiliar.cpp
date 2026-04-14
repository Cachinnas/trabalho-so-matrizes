#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

/**
 * Função para gerar uma matriz com valores aleatórios e salvar em arquivo.
 * O nome do arquivo agora inclui o caminho da pasta 'matrizes/'.
 */
void gerarMatriz(string nomeArquivo, int linhas, int colunas) {
    ofstream arquivo(nomeArquivo);
    if (!arquivo.is_open()) {
        cerr << "Erro: Nao foi possivel criar o arquivo '" << nomeArquivo << "'." << endl;
        cerr << "Certifique-se de que a pasta 'matrizes/' existe na raiz do projeto." << endl;
        return;
    }

    arquivo << linhas << " " << colunas << "\n";
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < colunas; j++) {
            // Gera números entre 0 e 99
            arquivo << rand() % 100 << " "; 
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

    // Converte argumentos de linha de comando para inteiros
    int n1 = stoi(argv[1]);
    int m1 = stoi(argv[2]);
    int n2 = stoi(argv[3]);
    int m2 = stoi(argv[4]);

    // Validação matemática para multiplicação de matrizes
    if (m1 != n2) {
        cout << "Erro: O numero de colunas da M1 (" << m1 << ") deve ser igual ao de linhas da M2 (" << n2 << ")." << endl;
        return 1;
    }

    // Inicializa a semente do gerador de números aleatórios
    srand(time(NULL)); 

    // CORREÇÃO: Caminhos ajustados para a pasta 'matrizes/'
    gerarMatriz("matrizes/M1.txt", n1, m1);
    gerarMatriz("matrizes/M2.txt", n2, m2);

    cout << "Matrizes M1 e M2 geradas com sucesso!" << endl;
    
    return 0;
}