#include <stdio.h>

// Função de Busca Sequencial com a técnica "Mover para a Frente"
int buscaMoverParaFrente(int vetor[], int tamanho, int chave) {
    for (int i = 0; i < tamanho; i++) {
        if (vetor[i] == chave) {
            // Se já estiver na frente, não precisa mover
            if (i == 0) return 0;

            // Guarda o elemento encontrado
            int aux = vetor[i];

            // Desloca os elementos anteriores para a direita 
            for (int j = i; j > 0; j--) {
                vetor[j] = vetor[j - 1];
            }

            // Reposiciona o elemento no início do vetor 
            vetor[0] = aux;

            return 0; // O elemento agora está no índice 0 
        }
    }
    return -1; // Elemento não encontrado 
}

// Função auxiliar para imprimir o vetor
void imprimirVetor(int vetor[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        printf("%d ", vetor[i]);
    }
    printf("\n");
}

int main() {
    int meuVetor[] = {12, 45, 7, 91, 34, 23};
    int tamanho = sizeof(meuVetor) / sizeof(meuVetor[0]);
    int chave = 91;

    printf("Vetor original: ");
    imprimirVetor(meuVetor, tamanho);

    int resultado = buscaMoverParaFrente(meuVetor, tamanho, chave);

    if (resultado != -1) {
        printf("Elemento %d encontrado e movido para a frente!\n", chave);
        printf("Vetor atualizado: ");
        imprimirVetor(meuVetor, tamanho);
    } else {
        printf("Elemento %d nao encontrado.\n", chave);
    }

    return 0;
}