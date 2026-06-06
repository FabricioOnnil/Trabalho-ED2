#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void prefixo(char pat[], int aux[], int m) {

    // j armazena o tamanho do maior prefixo que
    // também é sufixo até o índice anterior
    int j = 0;

    // aux[0] é sempre 0
    aux[0] = 0;

    int i = 1;
    while (i < m) {

        // Se os caracteres coincidem, incrementa o j e o i
        if (pat[i] == pat[j]) {
            j++;
            aux[i] = j;
            i++;
        }

        // Se houver uma diferença (mismatch)
        else {
            if (j != 0) {

                // Atualiza j para o valor anterior do aux
                // para evitar comparações redundantes
                j = aux[j - 1];
            }
            else {

                // Se não houver prefixo correspondente, define aux[i] como 0
                aux[i] = 0;
                i++;
            }
        }
    }

     // Impressão do vetor aux
    for(int i = 0; i < m; i++){
        printf("%d  ", aux[i]);
    }
    printf("\n");
}

int kmp(char pat[], char txt[]) {
    int n = strlen(txt);
    int m = strlen(pat);

    // Alocação dinâmica do vetor aux
    int *aux = (int *)malloc(m * sizeof(int));

    if (aux == NULL) {
        printf("Erro de alocação de memória\n");
        return -1;
    }

    prefixo(pat, aux, m);


    // Ponteiros i e j para percorrer
    // o texto e o padrão
    int i = 0, j = 0;

    while (i < n) {

        // Se os caracteres coincidem, avança ambos os ponteiros
        if (txt[i] == pat[j]) {
            i++;
            j++;

            // Se todo o padrão foi encontrado
            // retorna o índice inicial
            if (j == m) {
                free(aux);
                return i - j;
            }
        }

        // Se houver diferença (mismatch)
        else {

            // Usa o valor do aux anterior
            // para evitar comparações redundantes
            if (j != 0)
                j = aux[j - 1];
            else
                i++;
        }
    }

    // Liberação da memória antes de retornar
    free(aux);
    return -1;
}

int main() {
    char txt[] = "abaacaadaabaaba";
    char pat[] = "aaba";

    int encontrou = kmp(pat, txt);

    printf("%d", encontrou);

    return 0;
}