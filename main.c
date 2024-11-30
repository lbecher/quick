#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "aleatorio.h"
#include "central.h"
#include "mediana.h"

void executar_teste(FILE *csv, char *nome_arquivo, int tipo_teste, int execucoes) {
    srand(time(NULL));

    for (int i = 0; i < execucoes; i++) {
        clock_t inicio, inicio_total, fim, fim_total;
        double tempo, tempo_total;

        inicio_total = clock();

        // Abrir e ler o arquivo
        FILE *fp = fopen(nome_arquivo, "r");
        if (fp == NULL) {
            perror("Erro ao abrir o arquivo");
            return;
        }

        int count = 0;
        int num;
        while (fscanf(fp, "%d", &num) == 1) {
            count++;
        }

        int *V = (int *)malloc(count * sizeof(int));
        if (V == NULL) {
            fprintf(stderr, "Falha na alocação de memória\n");
            fclose(fp);
            return;
        }

        rewind(fp);
        int idx = 0;
        while (idx < count) {
            fscanf(fp, "%d", &V[idx]);
            idx++;
        }
        fclose(fp);
        
        inicio = clock();

        switch (tipo_teste) {
            case 0:
                quicksort_aleatorio(V, 0, count - 1);
                break;
            case 1:
                quicksort_central(V, 0, count - 1);
                break;
            case 2:
                quicksort_mediana(V, 0, count - 1);
                break;
        }

        fim = clock();
        
        free(V);

        fim_total = clock();

        tempo = ((double)(fim - inicio)) / CLOCKS_PER_SEC;
        tempo_total = ((double)(fim_total - inicio_total)) / CLOCKS_PER_SEC;

        if (i == 0)
            fprintf(csv, "%d,%lf,%lf", count, tempo, tempo_total);
        else
            fprintf(csv, ",%lf,%lf", tempo, tempo_total);
    }

    fprintf(csv, "\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }

    int execucoes = 6;

    char *nome_arquivo = argv[1];

    printf("Iniciando testes...\n");

    for (int tipo_teste = 0; tipo_teste < 3; tipo_teste++) {
        char csv_nome[80] = "";

        switch (tipo_teste) {
            case 0:
                strcat(csv_nome, "Aleatório.csv");
                break;
            case 1:
                strcat(csv_nome, "Central.csv");
                break;
            case 2:
                strcat(csv_nome, "Mediana.csv");
                break;
            default:
                printf("Tipo de teste inválido: %d\n", tipo_teste);
                return EXIT_FAILURE;
        }

        FILE *csv = fopen(csv_nome, "r+");
        if (csv == NULL) {
            // Se o arquivo não existe, cria-o em modo escrita e leitura ("w+")
            csv = fopen(csv_nome, "w+");

            if (csv == NULL) {
                perror("Erro ao criar o arquivo CSV");
                return EXIT_FAILURE;
            }

            for (int i = 0; i < execucoes; i++) {
                if (i == 0)
                    fprintf(csv, "count,tempo1,tempo_total1");
                else
                    fprintf(csv, ",tempo%d,tempo_total%d", i + 1, i + 1);
            }

            fprintf(csv, "\n");

            printf("Arquivo CSV não existia, mas foi criado.\n");
        } else {
            printf("Arquivo CSV aberto para leitura e escrita.\n");

            if (fseek(csv, 0, SEEK_END) != 0) {
                perror("Erro ao mover o cursor para o final do arquivo");
                fclose(csv);
                return EXIT_FAILURE;
            }
        }

        executar_teste(csv, nome_arquivo, tipo_teste, execucoes);

        fclose(csv);
    }

    printf("Testes concluídos.\n");
    return 0;
}