int medianaDeTres(int a, int b, int c) {
    if ((a <= b && b <= c) || (c <= b && b <= a)) return b;
    if ((b <= a && a <= c) || (c <= a && a <= b)) return a;
    return c;
}

void quickSortCentro(int v[], int esq, int dir) {
    int i = esq;
    int j = dir;
    int pivo = v[esq + (dir - esq) / 2];

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

    if (esq < j) quickSortCentro(v, esq, j);
    if (i < dir) quickSortCentro(v, i, dir);
}

void quickSortMediana(int v[], int esq, int dir) {
    int i = esq;
    int j = dir;
    int meio = esq + (dir - esq) / 2;
    int pivo = medianaDeTres(v[esq], v[meio], v[dir]);

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

    if (esq < j) quickSortMediana(v, esq, j);
    if (i < dir) quickSortMediana(v, i, dir);
}

/* Nomes esperados no enunciado */
void quicksortcentro(int v[], int esq, int dir) {
    quickSortCentro(v, esq, dir);
}

void quicksortmediana(int v[], int esq, int dir) {
    quickSortMediana(v, esq, dir);
}

/* Compatibilidade com código anterior */
void quickSort(int v[], int esq, int dir) {
    quickSortCentro(v, esq, dir);
}
