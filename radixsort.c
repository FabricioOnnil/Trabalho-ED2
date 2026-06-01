int obterMaior(int v[], int n) {
    int maior = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > maior) maior = v[i];
    return maior;
}

void countingSortParaRadix(int v[], int n, int exp) {
    int saida[n];
    int baldes[10] = {0};

    for (int i = 0; i < n; i++) baldes[(v[i] / exp) % 10]++;
    for (int i = 1; i < 10; i++) baldes[i] += baldes[i - 1];
    
    for (int i = n - 1; i >= 0; i--) {
        saida[baldes[(v[i] / exp) % 10] - 1] = v[i];
        baldes[(v[i] / exp) % 10]--;
    }
    for (int i = 0; i < n; i++) v[i] = saida[i];
}

void radixSort(int v[], int n) {
    int m = obterMaior(v, n);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        countingSortParaRadix(v, n, exp);
    }
}
