void quicksort_mediana(int *V, int inicio, int fim);
int particiona_mediana(int *V, int inicio, int final);
int mediana_de_tres(int *V, int inicio, int fim);

// f(n) = 20n + 63 -> O(n)
// a = 2, b = 2
void quicksort_mediana(int *V, int inicio, int fim) {
    if (inicio < fim) {                        // 1 -> 1 (melhor)
        int pivo = particiona_mediana(V, inicio, fim); // 2 + 20n + 56 -> 20n + 58
        quicksort_mediana(V, inicio, pivo - 1);        // 2
        quicksort_mediana(V, pivo + 1, fim);           // 2 = 20n + 63
    }
}

// Custo: f(n) = 20n + 56
int particiona_mediana(int *V, int inicio, int final) {
    int esq, dir, pivo, aux;

    int pivo_idx = mediana_de_tres(V, inicio, final); // 2 + 36 -> 38
    aux = V[inicio];                                  // 2
    V[inicio] = V[pivo_idx];                          // 3
    V[pivo_idx] = aux;                                // 2
    pivo = V[inicio];                                 // 2 = 47

    esq = inicio + 1;                                 // 2
    dir = final;                                      // 1 = 3

    while (esq <= dir) {                              // n
        while (esq <= final && V[esq] <= pivo)        // 4n
            esq++;                                    // 1 -> 1x (x + y = n) // x elementos na esquerda e y na direita
        while (dir > inicio && V[dir] > pivo)         // 4n
            dir--;                                    // 1 -> 1y = 10n

        if (esq < dir) {                              // 1 -> 1n (melhor)
            aux = V[esq];                             // 2 -> 2n
            V[esq] = V[dir];                          // 3 -> 3n
            V[dir] = aux;                             // 2 -> 2n
            esq++;                                    // 1 -> 1n
            dir--;                                    // 1 -> 1n = 10n (pior)
        }
    }

    V[inicio] = V[dir];                               // 3
    V[dir] = pivo;                                    // 2
    return dir;                                       // 1 = 6
}

// Custo: f(n) = 36
int mediana_de_tres(int *V, int inicio, int fim) {
    int intervalo = fim - inicio + 1;                                            // 3
    int idx1 = inicio + rand() % intervalo;                                      // 4
    int idx2 = inicio + rand() % intervalo;                                      // 4
    int idx3 = inicio + rand() % intervalo;                                      // 4 = 15

    int val1 = V[idx1];                                                          // 2
    int val2 = V[idx2];                                                          // 2
    int val3 = V[idx3];                                                          // 2 = 6

    if ((val1 <= val2 && val2 <= val3) || (val3 <= val2 && val2 <= val1))        // 7
        return idx2;                                                             // 1 -> 7 + 1  = 8 (melhor)
    else if ((val2 <= val1 && val1 <= val3) || (val3 <= val1 && val1 <= val2))   // 7
        return idx1;                                                             // 1 -> 7 + 7 + 1 = 15
    else
        return idx3;                                                             // 1 -> 7 + 7 + 1 = 15 (pior)
}