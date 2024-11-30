# -*- coding: utf-8 -*-
import matplotlib
matplotlib.use("TkAgg")  # Configura o backend para TkAgg

import os
import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

# Diretórios
directories = ["Aleatórios", "Ordenados", "ParcialmenteOrdenados", "Decrescentes"]

# Arquivos a serem lidos
files = ["Aleatório.csv", "Central.csv", "Mediana.csv"]

# Para armazenar os dados processados
data = {}

# Vetor de cores
colors = ["red", "blue", "green"]

# Leitura dos arquivos
for directory in directories:
    data[directory] = {}  # Cria uma chave para cada diretório
    for file in files:
        filepath = os.path.join(directory, file)
        if os.path.exists(filepath):
            df = pd.read_csv(filepath)

            # Ordenar pelo count
            df = df.sort_values(by="count")

            # Calcular a média ignorando `tempo1` e `tempo_total1`
            tempos = df[[col for col in df.columns if col.startswith('tempo') and not col.startswith('tempo_total') and col != 'tempo1']]
            tempos_totais = df[[col for col in df.columns if col.startswith('tempo_total') and col != 'tempo_total1']]

            # Médias
            media_tempos = tempos.mean(axis=1) * 1_000
            media_tempos_totais = tempos_totais.mean(axis=1) * 1_000

            # Armazenar os dados para o gráfico
            key = file.split('.')[0]
            data[directory][key] = {
                "count": df["count"],
                "media_tempos": media_tempos,
                "media_tempos_totais": media_tempos_totais
            }

# Criar gráficos separados por diretório
for directory, datasets in data.items():
    plt.figure(figsize=(8, 8))
    for idx, (key, values) in enumerate(datasets.items()):
        color = colors[idx % len(colors)]  # Atribuir cor com base no índice

        plt.plot(values["count"], values["media_tempos"], label=f"{key} - Ordenação", color=color)
        plt.plot(values["count"], values["media_tempos_totais"], linestyle='--', label=f"{key} - Ordenação + E/S", color=color)

    # Configurações do gráfico
    plt.ticklabel_format(style='plain', axis='x')
    plt.xlabel("Tamanho do vetor")
    plt.ylabel("Tempo de execução (ms)")
    plt.xticks(np.arange(0, 2_100_000, 100_000))
    plt.yticks(np.arange(0, 8_400, 400))
    plt.xticks(rotation=45) 
    plt.legend()
    plt.tight_layout()

    # Exibir gráfico
    plt.grid()
    plt.show()

# Criar gráficos separados por diretório com valores filtrados
for directory, datasets in data.items():
    plt.figure(figsize=(8, 8))
    for idx, (key, values) in enumerate(datasets.items()):
        color = colors[idx % len(colors)]  # Atribuir cor com base no índice

        # Filtrar valores acima de 30.000
        mask = values["count"] <= 5000
        filtered_count = values["count"][mask]
        filtered_media_tempos = values["media_tempos"][mask]
        filtered_media_tempos_totais = values["media_tempos_totais"][mask]

        # Plotar os valores filtrados
        plt.plot(filtered_count, filtered_media_tempos, label=f"{key} - Ordenação", color=color)
        plt.plot(filtered_count, filtered_media_tempos_totais, linestyle='--', label=f"{key} - Ordenação + E/S", color=color)

    # Configurações do gráfico
    plt.ticklabel_format(style='plain', axis='x')
    plt.xlabel("Tamanho do vetor")
    plt.ylabel("Tempo de execução (ms)")
    plt.xticks(np.arange(0, 5_250, 250))
    plt.yticks(np.arange(0, 15.75, 0.75))
    plt.xticks(rotation=45) 
    plt.legend()
    plt.tight_layout()

    # Exibir gráfico
    plt.grid()
    plt.show()
