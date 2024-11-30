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

# Leitura dos arquivos
for directory in directories:
    data[directory] = {}  # Cria uma chave para cada diretório
    for file in files:
        filepath = os.path.join(directory, file)
        if os.path.exists(filepath):
            df = pd.read_csv(filepath)
            
            # Calcular a média ignorando `tempo1` e `tempo_total1`
            tempos = df.filter(like='tempo').drop(['tempo1'], axis=1)
            tempos_totais = df.filter(like='tempo_total').drop(['tempo_total1'], axis=1)
            
            # Médias
            media_tempos = tempos.mean(axis=1)
            media_tempos_totais = tempos_totais.mean(axis=1)
            
            # Armazenar os dados para o gráfico
            key = file.split('.')[0]
            data[directory][key] = {
                "count": df["count"],
                "media_tempos": media_tempos,
                "media_tempos_totais": media_tempos_totais
            }

# Criar gráficos separados por diretório
for directory, datasets in data.items():
    plt.figure(figsize=(10, 7.5))
    for key, values in datasets.items():
        plt.plot(values["count"], values["media_tempos"], label=f"{key} Média Tempos")
        plt.plot(values["count"], values["media_tempos_totais"], linestyle='--', label=f"{key} Média Tempos Totais")
    
    # Configurações do gráfico
    plt.title(f"Comparação de Tempos - {directory}")
    plt.xlabel("Tamanho do vetor")
    plt.ylabel("Tempo de execução em segundos")
    plt.legend()
    plt.tight_layout()
    
    # Exibir gráfico
    plt.show()
