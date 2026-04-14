#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <unistd.h>
#include <sys/wait.h>
#include <string>

using namespace std;
using namespace std::chrono;

vector<vector<int>> M1, M2;
int n1, m1, m2;

void lerMatrizes(string arq1, string arq2) {
    ifstream arquivo1(arq1);
    arquivo1 >> n1 >> m1;
    M1.assign(n1, vector<int>(m1));
    for (int i = 0; i < n1; i++)
        for (int j = 0; j < m1; j++) arquivo1 >> M1[i][j];
    arquivo1.close();

    ifstream arquivo2(arq2);
    int n2;
    arquivo2 >> n2 >> m2;
    M2.assign(m1, vector<int>(m2));
    for (int i = 0; i < m1; i++)
        for (int j = 0; j < m2; j++) arquivo2 >> M2[i][j];
    arquivo2.close();
}

void multiplica_processo(int id, int linha_inicio, int linha_fim) {
    auto inicio = high_resolution_clock::now();
    vector<vector<int>> C_local(linha_fim - linha_inicio, vector<int>(m2, 0));

    for (int i = linha_inicio; i < linha_fim; i++) {
        for (int j = 0; j < m2; j++) {
            for (int k = 0; k < m1; k++) {
                C_local[i - linha_inicio][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    auto fim = high_resolution_clock::now();
    duration<double> tempo = fim - inicio;

    // CORREÇÃO: Salva em resultados/
    string nome_arq = "resultados/resultado_processo_" + to_string(id) + ".txt";
    ofstream saida(nome_arq);
    saida << (linha_fim - linha_inicio) << " " << m2 << "\n";
    for (int i = linha_inicio; i < linha_fim; i++) {
        for (int j = 0; j < m2; j++) {
            saida << "c" << i+1 << j+1 << " " << C_local[i - linha_inicio][j] << "\n";
        }
    }
    saida << tempo.count() << "\n";
    saida.close();
}

int main(int argc, char* argv[]) {
    if (argc != 4) { cout << "Uso: ./proc <M1> <M2> <P>\n"; return 1; }
    lerMatrizes(argv[1], argv[2]);
    int num_processos = stoi(argv[3]);

    int linhas_por_processo = n1 / num_processos;
    int resto = n1 % num_processos;
    int linha_atual = 0;

    for (int i = 0; i < num_processos; i++) {
        int linhas_deste_processo = linhas_por_processo + (i < resto ? 1 : 0);
        int linha_fim = linha_atual + linhas_deste_processo;
        pid_t pid = fork();
        if (pid == 0) {
            multiplica_processo(i, linha_atual, linha_fim);
            exit(0);
        }
        linha_atual = linha_fim;
    }

    for (int i = 0; i < num_processos; i++) wait(NULL);
    cout << "Processos concluídos. Resultados em resultados/" << endl;
    return 0;
}