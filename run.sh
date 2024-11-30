#!/bin/bash

# Compilar o arquivo main.c
gcc main.c -O2 -o main
if [ $? -ne 0 ]; then
  echo "Erro ao compilar main.c."
  exit 1
fi

echo "Compilação bem-sucedida. Gerando arquivos CSV para subdiretórios..."

# Listar e processar apenas os arquivos .txt nos diretórios especificados
for dir in Aleatórios Ordenados ParcialmenteOrdenados Decrescentes; do
  if [ -d "$dir" ]; then
    # Entrar no diretório
    cd "$dir"
    echo "Entrando no diretório: $dir"

    # Processar cada arquivo .txt no diretório atual
    find . -maxdepth 1 -type f -name "*.txt" | while read -r file; do
      # Remover o prefixo "./" do nome do arquivo
      file=${file#./}

      # Imprimir o arquivo que está sendo processado
      echo "Processando: $file"

      # Executar ./main a partir do diretório atual
      ../main "$file"
    done

    # Voltar ao diretório anterior
    cd ..
  else
    echo "Diretório não encontrado: $dir"
  fi
done
