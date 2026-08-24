#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct SYMBOL
{
    char alphabet;
    int frequency;
    struct SYMBOL *left;
    struct SYMBOL *right;
};

typedef struct SYMBOL SYMBOL;

SYMBOL *heap[100];
int heapSize = 0;

void swap(SYMBOL **a, SYMBOL **b)
{
    SYMBOL *temp = *a;
    *a = *b;
    *b = temp;
}

void insert(SYMBOL *node)
{
    int i = heapSize;
    heap[heapSize++] = node;

    while (i > 0)
    {
        int parent = (i - 1) / 2;

        if (heap[parent]->frequency <= heap[i]->frequency)
            break;

        swap(&heap[parent], &heap[i]);
        i = parent;
    }
}

SYMBOL *extractMin()
{
    SYMBOL *minNode;
    int i = 0;

    minNode = heap[0];
    heap[0] = heap[--heapSize];

    while (1)
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallest = i;

        if (left < heapSize &&
            heap[left]->frequency < heap[smallest]->frequency)
        {
            smallest = left;
        }

        if (right < heapSize &&
            heap[right]->frequency < heap[smallest]->frequency)
        {
            smallest = right;
        }

        if (smallest == i)
            break;

        swap(&heap[i], &heap[smallest]);
        i = smallest;
    }

    return minNode;
}

SYMBOL *createNode(char alphabet, int frequency)
{
    SYMBOL *node = (SYMBOL *)malloc(sizeof(SYMBOL));

    node->alphabet = alphabet;
    node->frequency = frequency;
    node->left = NULL;
    node->right = NULL;

    return node;
}

SYMBOL *buildHuffmanTree(int n)
{
    int i;
    SYMBOL *left, *right, *parent;

    for (i = 0; i < n; i++)
        insert(heap[i]);

    while (heapSize > 1)
    {
        left = extractMin();
        right = extractMin();

        parent = createNode('\0',
                            left->frequency + right->frequency);

        parent->left = left;
        parent->right = right;

        insert(parent);
    }

    return extractMin();
}

void inorder(SYMBOL *root)
{
    if (root == NULL)
        return;

    inorder(root->left);

    if (root->left == NULL && root->right == NULL)
        printf("%c ", root->alphabet);

    inorder(root->right);
}

int main()
{
    int n, i;
    char alphabets[100];
    int frequencies[100];

    SYMBOL *nodes[100];
    SYMBOL *root;

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    printf("Enter the number of distinct alphabets: ");
    scanf("%d", &n);

    printf("Enter the alphabets:\n");

    for (i = 0; i < n; i++)
        scanf(" %c", &alphabets[i]);

    printf("Enter its frequencies:\n");

    for (i = 0; i < n; i++)
        scanf("%d", &frequencies[i]);

    for (i = 0; i < n; i++)
        nodes[i] = createNode(alphabets[i], frequencies[i]);

    heapSize = 0;

    for (i = 0; i < n; i++)
        insert(nodes[i]);

    root = buildHuffmanTree(0);

    printf("\nIn-order traversal of the tree (Huffman): ");

    inorder(root);

    printf("\n");

    end = clock();

    cpu_time_used =
        ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("CPU Time Used: %f seconds\n", cpu_time_used);

    return 0;
}