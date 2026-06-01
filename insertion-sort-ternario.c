void insertionSortTernario(int v[], int n) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int esq = 0;
        int dir = i - 1;
        
        // Busca ternária para achar a posição de inserção
        while (esq <= dir) {
            int m1 = esq + (dir - esq) / 3;
            int m2 = dir - (dir - esq) / 3;
            
            if (chave < v[m1]) {
                dir = m1 - 1;
            } else if (chave > v[m2]) {
                esq = m2 + 1;
            } else {
                esq = m1 + 1;
                dir = m2 - 1;
            }
        }
        
        // Desloca os elementos para a direita
        for (int j = i - 1; j >= esq; j--) {
            v[j + 1] = v[j];
        }
        v[esq] = chave;
    }
}