#include <stdio.h>
#include <string.h>

#define MAXCHAR 256

int BMH(char *T, char *P)
{
    int i, j, k;
    int n = strlen(T);
    int m = strlen(P);
    int deslocamento[MAXCHAR];

    // pré-processamento
    for (j = 0; j < MAXCHAR; j++) {
        deslocamento[j] = m;
    }
    for (j = 1; j < m; j++) {
        deslocamento[(unsigned char)P[j - 1]] = m - j;
    }

    i = m;

    //print da tabela de pré-processamento
    for (int i =0; i < MAXCHAR; i++){
        printf("dec: %d - des: %d\n", i, deslocamento[i]);
    }
    printf("\n");

    // busca
    while (i <= n) {
        k = i;
        j = m;

        while (T[k-1] == P[j-1] && j > 0) {
            k--;
            j--;
        }

        if (j == 0)
            return k;

        i += deslocamento[(unsigned char)T[i - 1]];
    }

    return -1;
}

int main()
{
    char texto[] = "abracadabra";
    char padrao[] = "cada";

    int pos = BMH(texto, padrao);

    if (pos != -1)
        printf("Padrao encontrado na posicao: %d\n", pos);
    else
        printf("Padrao nao encontrado\n");

    return 0;
}