void quicksort_mediana(int *V, int inicio, int fim);
int particiona_mediana(int *V, int inicio, int final);
int mediana_de_tres(int *V, int inicio, int fim);

// f(n) = n + 133 -> O(n)
// 2(n/2) =>  n ^ log2 2 = n ^ 1 = n -> O(n)
//   O(n) ~= O(n) --> O(n log n)
void quicksort_mediana(int *V, int inicio, int fim) {
    if (inicio < fim) {                                // 1
        int pivo = particiona_mediana(V, inicio, fim); // 2 + n + 126 -> n + 128
        quicksort_mediana(V, inicio, pivo - 1);        // 2
        quicksort_mediana(V, pivo + 1, fim);           // 2 = n + 133
    }
}

// f(n) = n + 126
int particiona_mediana(int *V, int inicio, int final) {
    int esq, dir, pivo, aux;

    int pivo_idx = mediana_de_tres(V, inicio, final); // 2 + 66 -> 68
    aux = V[inicio];                                  // 2
    V[inicio] = V[pivo_idx];                          // 3
    V[pivo_idx] = aux;                                // 2
    pivo = V[inicio];                                 // 2 = 77

    esq = inicio + 1;                                 // 2
    dir = final;                                      // 1 = 3

    while (esq <= dir) {                              // 2(n/2 + 20) = n + 40

        while (esq <= final && V[esq] <= pivo)        // 4
            esq++;                                    // 1 = 5

        while (dir > inicio && V[dir] > pivo)         // 4
            dir--;                                    // 1 = 5

        if (esq < dir) {                              // 1
            aux = V[esq];                             // 2
            V[esq] = V[dir];                          // 3
            V[dir] = aux;                             // 2 
            esq++;                                    // 1
            dir--;                                    // 1 = 10
        }
    }

    V[inicio] = V[dir];                               // 3
    V[dir] = pivo;                                    // 2
    return dir;                                       // 1 = 6
}

// f(n) = 66
int mediana_de_tres(int *V, int inicio, int fim) {
    int intervalo = fim - inicio + 1;                                            // 3
    int idx1 = inicio + rand() % intervalo;                                      // 14 -> considerando rand() = 10 + 1 da chamada
    int idx2 = inicio + rand() % intervalo;                                      // 14
    int idx3 = inicio + rand() % intervalo;                                      // 14 = 45

    int val1 = V[idx1];                                                          // 2
    int val2 = V[idx2];                                                          // 2
    int val3 = V[idx3];                                                          // 2 = 6

    if ((val1 <= val2 && val2 <= val3) || (val3 <= val2 && val2 <= val1))        // 7
        return idx2;                                                             // 1 
    else if ((val2 <= val1 && val1 <= val3) || (val3 <= val1 && val1 <= val2))   // 7
        return idx1;                                                             // 1 
    else
        return idx3;                                                             // 1 -> 7 + 7 + 1 = 15 (pior)
}