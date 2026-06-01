void merge(int v[], int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    int E[n1], D[n2];

    for (int i = 0; i < n1; i++) E[i] = v[esq + i];
    for (int j = 0; j < n2; j++) D[j] = v[meio + 1 + j];

    int i = 0, j = 0, k = esq;
    while (i < n1 && j < n2) {
        if (E[i] <= D[j]) v[k++] = E[i++];
        else v[k++] = D[j++];
    }
    while (i < n1) v[k++] = E[i++];
    while (j < n2) v[k++] = D[j++];
}

void mergeSort(int v[], int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        mergeSort(v, esq, meio);
        mergeSort(v, meio + 1, dir);
        merge(v, esq, meio, dir);
    }
}
