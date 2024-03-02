#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct base
{
    int frequencia;
    char byte;
    // Next
    // Left
    // Right
};

struct node
{
    int item;
    int priority;
    struct node *next;
};

struct priority_queue
{
    struct node *head;
};
struct priority_queue *create_priority_queue()
{
    struct priority_queue *new_priority_queue = (struct priority_queue *)malloc(sizeof(struct priority_queue));
    new_priority_queue->head = NULL;
    return new_priority_queue;
}
int is_empty(struct priority_queue *pq)
{
    return (pq->head == NULL);
}
void enqueue(struct priority_queue *pq, int item, int priority)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->item = item;
    new_node->priority = priority;
    if ((is_empty(pq)) || (priority < pq->head->priority))
    {
        new_node->next = pq->head;
        pq->head = new_node;
    }
    else
    {
        struct node *current = pq->head;
        while ((current->next != NULL) && (current->next->priority < priority))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}

struct node *dequeue(struct priority_queue *pq)
{
    if (is_empty(pq))
    {
        printf("Priority Queue underflow");
        return NULL;
    }
    else
    {
        struct node *node = pq->head;
        pq->head = pq->head->next;
        node->next = NULL;
        return node;
    }
}

void printByteBinary(unsigned char byte)
{
    // Loop para percorrer cada bit do byte
    for (int i = 7; i >= 0; i--)
    {
        // Desloca o bit mais significativo (MSB) para a direita por i posições
        // e verifica se o resultado AND com 1 é igual a 1
        // Isso verifica se o bit na posição i é 1 ou 0
        printf("%d", (byte >> i) & 1);
    }
}
void leFrequencia(int *array)
{

    memset(array, 0, 256 * sizeof(int));
    char minhaString[30];
    scanf("%s", minhaString);              // Lê o nome do arquivo pelo usuário.
    FILE *file = fopen(minhaString, "rb"); // Lê os bits do arquivo, 'rb' -> Read Binary
    if (file == NULL)
    { // Se o arquivo não existir, retorna erro.
        perror("Error");
        return;
    }

    unsigned char byte;
    while (fscanf(file, "%c", &byte) != EOF)
    { // Lendo todo o arquivo até o seu final e armazenando a frequência no array.
        array[byte]++;
    }

    fclose(file); // Fecha o arquivo.
}

int main()
{
    /*
        Dado um arquivo, lê seus bits, e conta a frequência de cada bit em um array.

    */
    int frequencia[256]; // Array para armazenar a frequência de cada byte.
    leFrequencia(frequencia);

    struct priority_queue *pq = create_priority_queue(); // Criando a fila de prioridade.

    for (int x = 0; x < 256; x++)
    {
        if (frequencia[x] != 0)
        {
            enqueue(pq, x, frequencia[x]); // Adiciona o byte e sua frequência na fila de prioridade.
        }
    }

    while (pq->head != NULL)
    {
        struct node *node = dequeue(pq);
        printf("Byte: ");
        printByteBinary(node->item);
        printf(" Frequencia: %d\n", node->priority);
    }
    return 0;
}