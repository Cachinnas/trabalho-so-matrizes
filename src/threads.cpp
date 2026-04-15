#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <thread> 
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

void multiplica_thread(int id, int linha_inicio, int linha_fim) {
    // Inicia a contagem de tempo da fatia de trabalho desta thread
    auto inicio = high_resolution_clock::now();
    vector<vector<int>> C_local(linha_fim - linha_inicio, vector<int>(m2, 0));

    for (int i = linha_inicio; i < linha_fim; i++) {
        for (int j = 0; j < m2; j++) {
            for (int k = 0; k < m1; k++) {
                // Acessa as matrizes globais diretamente (memória compartilhada)
                C_local[i - linha_inicio][j] += M1[i][k] * M2[k][j];
            }
        }
    }

    auto fim = high_resolution_clock::now();
    duration<double> tempo = fim - inicio;

    string nome_arq = "resultados/resultado_thread_" + to_string(id) + ".txt";
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
    if (argc != 4) { cout << "Uso: ./thr <M1> <M2> <T>\n"; return 1; }
    lerMatrizes(argv[1], argv[2]);
    int num_threads = stoi(argv[3]);

    vector<thread> threads;
    int linhas_por_thread = n1 / num_threads;
    int resto = n1 % num_threads;
    int linha_atual = 0;

    for (int i = 0; i < num_threads; i++) {
        int linhas_desta_thread = linhas_por_thread + (i < resto ? 1 : 0);
        int linha_fim = linha_atual + linhas_desta_thread;
        // Dispara a thread passando o ID e o intervalo de linhas que ela vai processar
        threads.push_back(thread(multiplica_thread, i, linha_atual, linha_fim));
        linha_atual = linha_fim;
    }

    for (auto& th : threads) th.join();
    cout << "Threads concluídas. Resultados em resultados/" << endl;
    return 0;
}