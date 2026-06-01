#include <stdio.h>

// Função que implementa a Busca Sequencial Clássica
int buscaSequencial(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            return i; // Retorna o índice do elemento encontrado 
        }
    }
    return -1; // Retorna -1 caso a chave não seja encontrada 
}

int main() {
    int meuVetor[] = {12, 45, 7, 91, 34, 23};
    int tamanho = sizeof(meuVetor) / sizeof(meuVetor[0]);
    int chave = 91;

    int resultado = buscaSequencial(meuVetor, tamanho, chave);

    if (resultado != -1) {
        printf("Elemento %d encontrado no indice: %d\n", chave, resultado);
    } else {
        printf("Elemento %d nao encontrado.\n", chave);
    }

    return 0;
}