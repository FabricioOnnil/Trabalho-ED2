void quickSort(int v[], int esq, int dir) {
    int i = esq, j = dir;
    int pivo = v[esq + (dir - esq) / 2]; // Pivô central

    while (i <= j) {
        while (v[i] < pivo) i++;
        while (v[j] > pivo) j--;
        if (i <= j) {
            int aux = v[i];
            v[i] = v[j];
            v[j] = aux;
            i++;
            j--;
        }
    }
    if (esq < j) quickSort(v, esq, j);
    if (i < dir) quickSort(v, i, dir);
}
