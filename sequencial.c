#include <stdio.h>

int buscaPosicao(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            return i; // índice onde encontrou
        }
    }
    return -1;
}

int buscaValor(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            return vetor[i]; // valor encontrado
        }
    }
    return -1;
}


int buscaMoveToFront(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {

        if (vetor[i] == chave) {
            int encontrado = vetor[i];

            // empurrar elementos para a direita
            for (int j = i; j > 0; j--) {
                vetor[j] = vetor[j - 1];
            }

            // mover elemento para o início
            vetor[0] = encontrado;

            return encontrado;
        }
    }

    return -1; // não encontrou
}

int main() {
    int vetor[] = {5, 12, 8, 20, 3};
    int tamanho = sizeof(vetor) / sizeof(vetor[0]);
    int chave = 20;

    int pos = buscaPosicao(vetor, tamanho, chave);

    if (pos != -1)
        printf("Encontrado na posicao: %d\n", pos);
    else
        printf("Nao encontrado\n");
   
    int valor = buscaValor(vetor, tamanho, chave);

    if (valor != -1)
        printf("Encontrado valor: %d\n", valor);
    else
        printf("Nao encontrado\n");

    valor = buscaMoveToFront(vetor, tamanho, chave);

    if (valor != -1)
        printf("Encontrado valor: %d\n", valor);
    else
        printf("Nao encontrado\n");

    return 0;
}