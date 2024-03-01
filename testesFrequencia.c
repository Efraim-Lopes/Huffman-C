#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void printByteBinary(unsigned char byte) {
    // Loop para percorrer cada bit do byte
    for (int i = 7; i >= 0; i--) {
        // Desloca o bit mais significativo (MSB) para a direita por i posições
        // e verifica se o resultado AND com 1 é igual a 1
        // Isso verifica se o bit na posição i é 1 ou 0
        printf("%d", (byte >> i) & 1);
    }
}

int main() {
    /*
        Dado um arquivo, lê seus bits, e conta a frequência de cada bit em um array.
        
    */
    char minhaString[30];
    scanf("%s", minhaString); // Lê o nome do arquivo pelo usuário.
    FILE *file = fopen(minhaString, "rb"); // Lê os bits do arquivo, 'rb' -> Read Binary
    if(file == NULL) { // Se o arquivo não existir, retorna erro.
        perror ("Error");
        return 0;
    }

    int frequencia[256]; // Array para armazenar a frequência de cada bit 256 = 2^8
    memset(frequencia, 0, sizeof(frequencia)); // Seta todos os valores do array para 0.
    unsigned char byte;
    while (fscanf(file,"%c",&byte) != EOF) { // Lendo todo o arquivo até o seu final e armazenando a frequência no array.
        frequencia[byte]++;
    }
    fclose(file); // Fecha o arquivo.

    for(int x = 0; x < 256; x++) {
        if(frequencia[x] != 0) {
            printf("Byte: ");
            printByteBinary(x); // Printa o byte.
            printf(" %d\n", frequencia[x]); // Printa a frequência de cada byte.
        }
    }
    return 0;
}