#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

struct node
{
    int item;
    int priority;
    struct node *next;
    struct node *left;
    struct node *right;
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
    new_node->right = NULL;
    new_node->left = NULL;
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
void enqueueWithNode(struct priority_queue *pq, struct node* no)
{
    if ((is_empty(pq)) || (no->priority < pq->head->priority))
    {
        no->next = pq->head;
        pq->head = no;
    }
    else
    {
        struct node *current = pq->head;
        while ((current->next != NULL) && (current->next->priority < no->priority))
        {
            current = current->next;
        }
        no->next = current->next;
        current->next = no;
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
void printPreOrder(struct node *node)
{
    if (node != NULL)
    {
        printf("%c %d\n", node->item, node->priority);
        printPreOrder(node->left);
        printPreOrder(node->right);
    }
}
int main()
{
    /*
        Dado um arquivo, lê seus bits, e conta a frequência de cada bit em um array.
        Criar fila de prioridade.
        Espaçar a fila em arvóres.
    */
    int frequencia[256]; // Array para armazenar a frequência de cada byte.
    leFrequencia(frequencia);

    struct priority_queue *pq = create_priority_queue(); // Criando a fila de prioridade.

    for (int x = 0; x < 256; x++)
        if (frequencia[x] != 0) enqueue(pq, x, frequencia[x]); // Adiciona o byte e sua frequência na fila de prioridade.
    printf("\n");

    while(pq->head->next != NULL){ // Espaçando a fila de prioridade em arvóres.
        struct node *left = dequeue(pq);
        struct node *right = dequeue(pq);
        // s {1}
        struct node *new_node = (struct node *)malloc(sizeof(struct node));
        new_node->item = -1; // * = -1;
        new_node->priority = left->priority + right->priority;
        new_node->left = left;
        new_node->right = right;
        enqueueWithNode(pq, new_node);
    }
    // Teoricamente espaçei a fila de prioridade em arvóres.
    printPreOrder(pq->head);
    return 0;
}