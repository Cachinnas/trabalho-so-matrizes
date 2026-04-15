import matplotlib.pyplot as plt

threads_tempos = [117.177, 79.95, 64.604, 68.811]
processos_tempos = [150, 180, 120, 160]
sequencial_medio = 236.182
eixo_x = [2, 4, 8, 16]

plt.figure(figsize=(10, 6))

plt.axhline(y=sequencial_medio, color='r', linestyle='--', label=f'Sequencial ({sequencial_medio}s)')

plt.plot(eixo_x, threads_tempos, marker='o', label='Threads', color='blue', linewidth=2)
plt.plot(eixo_x, processos_tempos, marker='s', label='Processos', color='green', linewidth=2)

plt.title('Comparativo de Desempenho: Sequencial vs Paralelo', fontsize=14)
plt.xlabel('Quantidade de Threads / Processos', fontsize=12)
plt.ylabel('Tempo de Execução (segundos)', fontsize=12)
plt.xticks(eixo_x)
plt.grid(True, which='both', linestyle='--', alpha=0.5)
plt.legend()

plt.savefig('grafico_desempenho.png')
plt.show()