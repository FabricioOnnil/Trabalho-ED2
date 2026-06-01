void shellSort(int v[], int n) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int chave = v[i];
            int j = i;
            while (j >= gap && v[j - gap] > chave) {
                v[j] = v[j - gap];
                j -= gap;
            }
            v[j] = chave;
        }
    }
}