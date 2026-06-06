#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct {
    unsigned long long comparacoes;
    unsigned long long trocas;
} Stats;

static double agora_segundos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1000000000.0;
}

static int eq_icase(const char *a, const char *b) {
    while (*a && *b) {
        if (tolower((unsigned char)*a) != tolower((unsigned char)*b)) {
            return 0;
        }
        a++;
        b++;
    }
    return *a == '\0' && *b == '\0';
}

static void troca(int *a, int *b, Stats *s) {
    int t = *a;
    *a = *b;
    *b = t;
    s->trocas++;
}

static int obter_maior(int v[], int n, Stats *s) {
    int maior = v[0];
    for (int i = 1; i < n; i++) {
        s->comparacoes++;
        if (v[i] > maior) {
            maior = v[i];
        }
    }
    return maior;
}

static void bubble_sort(int v[], int n, Stats *s) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            s->comparacoes++;
            if (v[j] > v[j + 1]) {
                troca(&v[j], &v[j + 1], s);
            }
        }
    }
}

static void bubble_sort_parada(int v[], int n, Stats *s) {
    for (int i = 0; i < n - 1; i++) {
        int trocou = 0;
        for (int j = 0; j < n - i - 1; j++) {
            s->comparacoes++;
            if (v[j] > v[j + 1]) {
                troca(&v[j], &v[j + 1], s);
                trocou = 1;
            }
        }
        if (!trocou) {
            break;
        }
    }
}

static void insertion_sort(int v[], int n, Stats *s) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            s->comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                s->trocas++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
        s->trocas++;
    }
}

static int busca_binaria_pos(int v[], int chave, int inicio, int fim, Stats *s) {
    int esq = inicio;
    int dir = fim;

    while (esq <= dir) {
        int meio = esq + (dir - esq) / 2;
        s->comparacoes++;
        if (chave < v[meio]) {
            dir = meio - 1;
        } else {
            esq = meio + 1;
        }
    }
    return esq;
}

static void insertion_sort_binario(int v[], int n, Stats *s) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int pos = busca_binaria_pos(v, chave, 0, i - 1, s);

        for (int j = i - 1; j >= pos; j--) {
            v[j + 1] = v[j];
            s->trocas++;
        }
        v[pos] = chave;
        s->trocas++;
    }
}

static int busca_ternaria_pos(int v[], int chave, int inicio, int fim, Stats *s) {
    int esq = inicio;
    int dir = fim;

    while (esq <= dir) {
        int m1 = esq + (dir - esq) / 3;
        int m2 = dir - (dir - esq) / 3;

        s->comparacoes++;
        if (chave < v[m1]) {
            dir = m1 - 1;
            continue;
        }

        s->comparacoes++;
        if (chave > v[m2]) {
            esq = m2 + 1;
            continue;
        }

        esq = m1 + 1;
        dir = m2 - 1;
    }
    return esq;
}

static void insertion_sort_ternario(int v[], int n, Stats *s) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int pos = busca_ternaria_pos(v, chave, 0, i - 1, s);

        for (int j = i - 1; j >= pos; j--) {
            v[j + 1] = v[j];
            s->trocas++;
        }
        v[pos] = chave;
        s->trocas++;
    }
}

static void shell_sort(int v[], int n, Stats *s) {
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            int chave = v[i];
            int j = i;

            while (j >= gap) {
                s->comparacoes++;
                if (v[j - gap] > chave) {
                    v[j] = v[j - gap];
                    s->trocas++;
                    j -= gap;
                } else {
                    break;
                }
            }
            v[j] = chave;
            s->trocas++;
        }
    }
}

static void selection_sort(int v[], int n, Stats *s) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            s->comparacoes++;
            if (v[j] < v[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            troca(&v[min_idx], &v[i], s);
        }
    }
}

static void heapify(int v[], int n, int i, Stats *s) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    if (esq < n) {
        s->comparacoes++;
        if (v[esq] > v[maior]) {
            maior = esq;
        }
    }
    if (dir < n) {
        s->comparacoes++;
        if (v[dir] > v[maior]) {
            maior = dir;
        }
    }

    if (maior != i) {
        troca(&v[i], &v[maior], s);
        heapify(v, n, maior, s);
    }
}

static void heap_sort(int v[], int n, Stats *s) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(v, n, i, s);
    }
    for (int i = n - 1; i > 0; i--) {
        troca(&v[0], &v[i], s);
        heapify(v, i, 0, s);
    }
}

static int mediana_de_tres(int a, int b, int c, Stats *s) {
    s->comparacoes += 2;
    if ((a <= b && b <= c) || (c <= b && b <= a)) {
        return b;
    }

    s->comparacoes += 2;
    if ((b <= a && a <= c) || (c <= a && a <= b)) {
        return a;
    }
    return c;
}

static void quick_sort_centro_rec(int v[], int esq, int dir, Stats *s) {
    int i = esq;
    int j = dir;
    int pivo = v[esq + (dir - esq) / 2];

    while (i <= j) {
        while (i <= dir) {
            s->comparacoes++;
            if (v[i] < pivo) {
                i++;
            } else {
                break;
            }
        }
        while (j >= esq) {
            s->comparacoes++;
            if (v[j] > pivo) {
                j--;
            } else {
                break;
            }
        }

        if (i <= j) {
            troca(&v[i], &v[j], s);
            i++;
            j--;
        }
    }

    if (esq < j) {
        quick_sort_centro_rec(v, esq, j, s);
    }
    if (i < dir) {
        quick_sort_centro_rec(v, i, dir, s);
    }
}

static void quick_sort_mediana_rec(int v[], int esq, int dir, Stats *s) {
    int i = esq;
    int j = dir;
    int meio = esq + (dir - esq) / 2;
    int pivo = mediana_de_tres(v[esq], v[meio], v[dir], s);

    while (i <= j) {
        while (i <= dir) {
            s->comparacoes++;
            if (v[i] < pivo) {
                i++;
            } else {
                break;
            }
        }
        while (j >= esq) {
            s->comparacoes++;
            if (v[j] > pivo) {
                j--;
            } else {
                break;
            }
        }

        if (i <= j) {
            troca(&v[i], &v[j], s);
            i++;
            j--;
        }
    }

    if (esq < j) {
        quick_sort_mediana_rec(v, esq, j, s);
    }
    if (i < dir) {
        quick_sort_mediana_rec(v, i, dir, s);
    }
}

static void merge(int v[], int esq, int meio, int dir, Stats *s) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;
    int *e = (int *)malloc((size_t)n1 * sizeof(int));
    int *d = (int *)malloc((size_t)n2 * sizeof(int));

    if (!e || !d) {
        free(e);
        free(d);
        fprintf(stderr, "Erro de memoria no merge.\n");
        exit(1);
    }

    for (int i = 0; i < n1; i++) {
        e[i] = v[esq + i];
    }
    for (int j = 0; j < n2; j++) {
        d[j] = v[meio + 1 + j];
    }

    int i = 0;
    int j = 0;
    int k = esq;

    while (i < n1 && j < n2) {
        s->comparacoes++;
        if (e[i] <= d[j]) {
            v[k++] = e[i++];
        } else {
            v[k++] = d[j++];
        }
        s->trocas++;
    }

    while (i < n1) {
        v[k++] = e[i++];
        s->trocas++;
    }
    while (j < n2) {
        v[k++] = d[j++];
        s->trocas++;
    }

    free(e);
    free(d);
}

static void merge_sort_rec(int v[], int esq, int dir, Stats *s) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        merge_sort_rec(v, esq, meio, s);
        merge_sort_rec(v, meio + 1, dir, s);
        merge(v, esq, meio, dir, s);
    }
}

static void counting_sort_radix(int v[], int n, int exp, Stats *s) {
    int *saida = (int *)malloc((size_t)n * sizeof(int));
    int baldes[10] = {0};

    if (!saida) {
        fprintf(stderr, "Erro de memoria no radix sort.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        baldes[(v[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; i++) {
        baldes[i] += baldes[i - 1];
    }

    for (int i = n - 1; i >= 0; i--) {
        int dig = (v[i] / exp) % 10;
        saida[baldes[dig] - 1] = v[i];
        baldes[dig]--;
        s->trocas++;
    }
    for (int i = 0; i < n; i++) {
        v[i] = saida[i];
        s->trocas++;
    }

    free(saida);
}

static void radix_sort(int v[], int n, Stats *s) {
    int m = obter_maior(v, n, s);
    for (int exp = 1; m / exp > 0; exp *= 10) {
        counting_sort_radix(v, n, exp, s);
    }
}

static void insertion_sort_bucket(int v[], int n, Stats *s) {
    for (int i = 1; i < n; i++) {
        int chave = v[i];
        int j = i - 1;

        while (j >= 0) {
            s->comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                s->trocas++;
                j--;
            } else {
                break;
            }
        }
        v[j + 1] = chave;
        s->trocas++;
    }
}

static void bucket_sort(int v[], int n, Stats *s) {
    const int num_baldes = 10;
    int maior = obter_maior(v, n, s);
    int *baldes = (int *)malloc((size_t)num_baldes * (size_t)n * sizeof(int));
    int *cont = (int *)calloc((size_t)num_baldes, sizeof(int));

    if (!baldes || !cont) {
        free(baldes);
        free(cont);
        fprintf(stderr, "Erro de memoria no bucket sort.\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        int idx = (v[i] * num_baldes) / (maior + 1);
        baldes[idx * n + cont[idx]] = v[i];
        cont[idx]++;
        s->trocas++;
    }

    int k = 0;
    for (int b = 0; b < num_baldes; b++) {
        if (cont[b] > 0) {
            insertion_sort_bucket(&baldes[b * n], cont[b], s);
            for (int j = 0; j < cont[b]; j++) {
                v[k++] = baldes[b * n + j];
                s->trocas++;
            }
        }
    }

    free(baldes);
    free(cont);
}

static int carregar_entrada(const char *caminho, int **vetor, int *n) {
    FILE *f = fopen(caminho, "r");
    if (!f) {
        return 0;
    }

    int cap = 1024;
    int qtd = 0;
    int *v = (int *)malloc((size_t)cap * sizeof(int));
    if (!v) {
        fclose(f);
        return 0;
    }

    int x;
    while (fscanf(f, "%d", &x) == 1) {
        if (qtd == cap) {
            cap *= 2;
            int *novo = (int *)realloc(v, (size_t)cap * sizeof(int));
            if (!novo) {
                free(v);
                fclose(f);
                return 0;
            }
            v = novo;
        }
        v[qtd++] = x;
    }

    fclose(f);
    *vetor = v;
    *n = qtd;
    return 1;
}

static int salvar_saida(const char *caminho, int v[], int n, const Stats *s, double tempo_seg) {
    FILE *f = fopen(caminho, "w");
    if (!f) {
        return 0;
    }

    for (int i = 0; i < n; i++) {
        fprintf(f, "%d\n", v[i]);
    }

    fprintf(f, "Numero de comparacoes: %llu\n", s->comparacoes);
    fprintf(f, "Numero de trocas: %llu\n", s->trocas);
    fprintf(f, "Tempo de execucao (s): %.9f\n", tempo_seg);
    fclose(f);
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr,
                "Uso: %s <algoritmo> <arquivo_entrada> [arquivo_saida]\n"
                "Algoritmos: bolha, bolha_parada, insercao, insercao_binaria,\n"
                "            insercao_ternaria, shell, selecao, heap,\n"
                "            quick_centro, quick_mediana, merge, radix, bucket\n",
                argv[0]);
        return 1;
    }

    const char *alg = argv[1];
    const char *entrada = argv[2];
    const char *saida = (argc >= 4) ? argv[3] : "saida.txt";

    int *v = NULL;
    int n = 0;
    if (!carregar_entrada(entrada, &v, &n)) {
        fprintf(stderr, "Erro ao ler arquivo de entrada: %s\n", entrada);
        return 1;
    }

    Stats s = {0, 0};
    double ini = agora_segundos();

    if (n > 1) {
        if (eq_icase(alg, "bolha")) {
            bubble_sort(v, n, &s);
        } else if (eq_icase(alg, "bolha_parada") || eq_icase(alg, "bolha-parada")) {
            bubble_sort_parada(v, n, &s);
        } else if (eq_icase(alg, "insercao")) {
            insertion_sort(v, n, &s);
        } else if (eq_icase(alg, "insercao_binaria") || eq_icase(alg, "insertion-bin")) {
            insertion_sort_binario(v, n, &s);
        } else if (eq_icase(alg, "insercao_ternaria") || eq_icase(alg, "insertion-ternario")) {
            insertion_sort_ternario(v, n, &s);
        } else if (eq_icase(alg, "shell") || eq_icase(alg, "shell-sort")) {
            shell_sort(v, n, &s);
        } else if (eq_icase(alg, "selecao") || eq_icase(alg, "selection")) {
            selection_sort(v, n, &s);
        } else if (eq_icase(alg, "heap") || eq_icase(alg, "heapsort")) {
            heap_sort(v, n, &s);
        } else if (eq_icase(alg, "quick_centro") || eq_icase(alg, "quicksortcentro")) {
            quick_sort_centro_rec(v, 0, n - 1, &s);
        } else if (eq_icase(alg, "quick_mediana") || eq_icase(alg, "quicksortmediana")) {
            quick_sort_mediana_rec(v, 0, n - 1, &s);
        } else if (eq_icase(alg, "merge") || eq_icase(alg, "mergesort")) {
            merge_sort_rec(v, 0, n - 1, &s);
        } else if (eq_icase(alg, "radix") || eq_icase(alg, "radixsort")) {
            radix_sort(v, n, &s);
        } else if (eq_icase(alg, "bucket") || eq_icase(alg, "bucketsort")) {
            bucket_sort(v, n, &s);
        } else {
            fprintf(stderr, "Algoritmo invalido: %s\n", alg);
            free(v);
            return 1;
        }
    }

    double fim = agora_segundos();
    double tempo_seg = fim - ini;

    if (!salvar_saida(saida, v, n, &s, tempo_seg)) {
        fprintf(stderr, "Erro ao escrever arquivo de saida: %s\n", saida);
        free(v);
        return 1;
    }

    printf("Arquivo gerado: %s\n", saida);
    printf("Numero de comparacoes: %llu\n", s.comparacoes);
    printf("Numero de trocas: %llu\n", s.trocas);
    printf("Tempo de execucao (s): %.9f\n", tempo_seg);

    free(v);
    return 0;
}
