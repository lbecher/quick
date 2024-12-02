void quicksort_aleatorio(int *V, int inicio, int fim);
int particiona_aleatorio(int *V, int inicio, int final);

//f(n) = n + 84 -> O(n)
// 2(n/2) =>  n ^ log2 2 = n ^ 1 = n -> O(n)
//   O(n) ~= O(n) --> O(n log n)
void quicksort_aleatorio(int *V, int inicio, int fim) {
    if (inicio < fim) { //1
        int pivo = particiona_aleatorio(V, inicio, fim); //2 + n + 77 -> n + 79
        quicksort_aleatorio(V, inicio, pivo - 1); //2
        quicksort_aleatorio(V, pivo + 1, fim); //2
    }
}

//f(n) =  n + 77
int particiona_aleatorio(int *V, int inicio, int final) {
    int esq, dir, pivo, aux;

    // Escolha aleatória do pivô
    int pivo_idx = inicio + rand() % (final - inicio + 1); // 5
    aux = V[inicio]; // 2
    V[inicio] = V[pivo_idx]; //3
    V[pivo_idx] = aux; // 2
    pivo = V[inicio]; //2

    esq = inicio + 1; //2
    dir = final; // 1

    while (esq <= dir) { //2(n/2 + 20)  -> n + 40
        while (esq <= final && V[esq] <= pivo) //4 
            esq++; //1
        while (dir > inicio && V[dir] > pivo) // 4
            dir--; //1

        if (esq < dir) { //1
            aux = V[esq]; //2
            V[esq] = V[dir]; //3
            V[dir] = aux; //2
            esq++;  //1
            dir--; //1
        }
    }

    V[inicio] = V[dir]; //3
    V[dir] = pivo; //2
    return dir; //1
}
