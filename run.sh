#!/bin/bash

# Compilar o arquivo main.c
gcc main.c -o main
if [ $? -ne 0 ]; then
  echo "Erro ao compilar main.c."
  exit 1
fi

echo "Compilação bem-sucedida. Gerando arquivos CSV para subdiretórios..."

# Encontrar e processar cada arquivo .txt nos subdiretórios
find ./ -type f -name "*.txt" | while read -r file; do
  # Obter o diretório do arquivo
  dir=$(dirname "$file")

  # Imprimir o arquivo que está sendo processado
  echo "Processando: $file"

  # Executar ./main
  ./main "$file"
done