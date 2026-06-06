#define NUM_BALDES 10

static int bucketObterMaior(int v[], int n) {
    int maior = v[0];
    for (int i = 1; i < n; i++) {
        if (v[i] > maior) maior = v[i];
    }
    return maior;
}

static void bucketInsertionSort(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        while (j >= 0 && v[j] > chave) {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = chave;
    }
}

void bucketSort(int v[], int n) {
    int maior = bucketObterMaior(v, n);
    
    // Matriz para simular baldes dinâmicos simples
    int baldes[NUM_BALDES][n];
    int contadoresBaldes[NUM_BALDES] = {0};

    // Distribui os elementos nos baldes baseando-se no valor relativo ao maior
    for (int i = 0; i < n; i++) {
        int idxBalde = (v[i] * NUM_BALDES) / (maior + 1);
        baldes[idxBalde][contadoresBaldes[idxBalde]++] = v[i];
    }

    // Ordena cada balde individualmente e concatena no vetor original
    int idxVetor = 0;
    for (int i = 0; i < NUM_BALDES; i++) {
        if (contadoresBaldes[i] > 0) {
            bucketInsertionSort(baldes[i], contadoresBaldes[i]);
            for (int j = 0; j < contadoresBaldes[i]; j++) {
                v[idxVetor++] = baldes[i][j];
            }
        }
    }
}
