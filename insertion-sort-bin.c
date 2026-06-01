void insertionSortBinario(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int esq = 0;
        int dir = i - 1;
        
        // Busca binária para achar a posição de inserção
        while (esq <= dir) {
            int meio = esq + (dir - esq) / 2;
            if (chave < v[meio]) dir = meio - 1;
            else esq = meio + 1;
        }
        
        // Desloca os elementos para a direita
        for (int j = i - 1; j >= esq; j--) {
            v[j + 1] = v[j];
        }
        v[esq] = chave;
    }
}
