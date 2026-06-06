#include <stdio.h>

int buscaBinaria(int vetor[], int tamanho, int K) {
    int inicio = 0;
    int fim = tamanho - 1;

    while (inicio <= fim) {
        int meio = (inicio + fim) / 2;

        if (vetor[meio] == K) {
            return meio; // encontrou
        }
        else if (vetor[meio] > K) {
            fim = meio - 1; // esquerda
        }
        else {
            inicio = meio + 1; // direita
        }
    }

    return -1; // não encontrou
}

int buscaBinariaRec(int vetor[], int chave, int inicio, int fim) {
    // caso base: não encontrou
    if (inicio > fim) {
        return -1;
    }

    int meio = (inicio + fim) / 2;

    // encontrou
    if (vetor[meio] == chave) {
        return meio;
    }
    // busca na metade esquerda
    else if (vetor[meio] > chave) {
        return buscaBinariaRec(vetor, chave, inicio, meio - 1);
    }
    // busca na metade direita
    else {
        return buscaBinariaRec(vetor, chave, meio + 1, fim);
    }
}

int main() {
    int V[] = {2, 5, 8, 12, 20, 30};
    int n = sizeof(V) / sizeof(V[0]);
    int K = 20;

    int pos = buscaBinaria(V, n, K);

    if (pos != -1)
        printf("Encontrado na posicao: %d\n", pos);
    else
        printf("Nao encontrado\n");
    
    pos = buscaBinariaRec(V, K, 0, n - 1);

    if (pos != -1)
        printf("Encontrado na posicao: %d\n", pos);
    else
        printf("Nao encontrado\n");

    return 0;
}