void quicksort_aleatorio(int *V, int inicio, int fim);
int particiona_aleatorio(int *V, int inicio, int final);

void quicksort_aleatorio(int *V, int inicio, int fim) {
    if (inicio < fim) {
        int pivo = particiona_aleatorio(V, inicio, fim);
        quicksort_aleatorio(V, inicio, pivo - 1);
        quicksort_aleatorio(V, pivo + 1, fim);
    }
}

int particiona_aleatorio(int *V, int inicio, int final) {
    int esq, dir, pivo, aux;

    // Escolha aleatória do pivô
    int pivo_idx = inicio + rand() % (final - inicio + 1);
    aux = V[inicio];
    V[inicio] = V[pivo_idx];
    V[pivo_idx] = aux;
    pivo = V[inicio];

    esq = inicio + 1;
    dir = final;

    while (esq <= dir) {
        while (esq <= final && V[esq] <= pivo)
            esq++;
        while (dir > inicio && V[dir] > pivo)
            dir--;

        if (esq < dir) {
            aux = V[esq];
            V[esq] = V[dir];
            V[dir] = aux;
            esq++;
            dir--;
        }
    }

    V[inicio] = V[dir];
    V[dir] = pivo;
    return dir;
}