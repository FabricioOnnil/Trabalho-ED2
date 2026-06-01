void selectionSort(int v[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            if (v[j] < v[min_idx]) {
                min_idx = j;
            }
        }
        int aux = v[min_idx];
        v[min_idx] = v[i];
        v[i] = aux;
    }
}
