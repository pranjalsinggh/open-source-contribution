#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *left;
    struct Node *right;
} Node;

typedef enum {
    INSERTED,
    DUPLICATE,
    ALLOCATION_FAILED
} InsertResult;

static InsertResult insert(Node **root, int value)
{
    if (*root == NULL) {
        Node *node = malloc(sizeof(*node));
        if (node == NULL) {
            return ALLOCATION_FAILED;
        }

        node->value = value;
        node->left = NULL;
        node->right = NULL;
        *root = node;
        return INSERTED;
    }

    if (value == (*root)->value) {
        return DUPLICATE;
    }

    if (value < (*root)->value) {
        return insert(&(*root)->left, value);
    }

    return insert(&(*root)->right, value);
}

static const Node *search(const Node *root, int value)
{
    while (root != NULL) {
        if (value == root->value) {
            return root;
        }
        root = value < root->value ? root->left : root->right;
    }

    return NULL;
}

static void print_in_order(const Node *root)
{
    if (root == NULL) {
        return;
    }

    print_in_order(root->left);
    printf("%d ", root->value);
    print_in_order(root->right);
}

static void free_tree(Node *root)
{
    if (root == NULL) {
        return;
    }

    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

int main(void)
{
    const int values[] = {8, 3, 10, 1, 6, 14, 4, 7, 13, 6};
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    Node *root = NULL;

    for (size_t i = 0; i < value_count; i++) {
        InsertResult result = insert(&root, values[i]);
        if (result == ALLOCATION_FAILED) {
            fprintf(stderr, "Could not allocate a tree node.\n");
            free_tree(root);
            return EXIT_FAILURE;
        }
        if (result == DUPLICATE) {
            printf("Ignored duplicate value: %d\n", values[i]);
        }
    }

    printf("In-order traversal: ");
    print_in_order(root);
    printf("\n");

    printf("Search for 7: %s\n", search(root, 7) != NULL ? "found" : "not found");
    printf("Search for 2: %s\n", search(root, 2) != NULL ? "found" : "not found");

    free_tree(root);
    return EXIT_SUCCESS;
}
