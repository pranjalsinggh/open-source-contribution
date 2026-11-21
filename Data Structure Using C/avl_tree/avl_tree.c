#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    int height;
    struct Node *left;
    struct Node *right;
} Node;

static int height(const Node *node)
{
    return node == NULL ? 0 : node->height;
}

static int maximum(int first, int second)
{
    return first > second ? first : second;
}

static Node *create_node(int key)
{
    Node *node = malloc(sizeof(*node));

    if (node == NULL) {
        fputs("Unable to allocate memory for a tree node.\n", stderr);
        exit(EXIT_FAILURE);
    }

    node->key = key;
    node->height = 1;
    node->left = NULL;
    node->right = NULL;
    return node;
}

static Node *rotate_right(Node *root)
{
    Node *new_root = root->left;
    Node *transferred_subtree = new_root->right;

    new_root->right = root;
    root->left = transferred_subtree;

    root->height = 1 + maximum(height(root->left), height(root->right));
    new_root->height = 1 + maximum(height(new_root->left), height(new_root->right));
    return new_root;
}

static Node *rotate_left(Node *root)
{
    Node *new_root = root->right;
    Node *transferred_subtree = new_root->left;

    new_root->left = root;
    root->right = transferred_subtree;

    root->height = 1 + maximum(height(root->left), height(root->right));
    new_root->height = 1 + maximum(height(new_root->left), height(new_root->right));
    return new_root;
}

static int balance_factor(const Node *node)
{
    return node == NULL ? 0 : height(node->left) - height(node->right);
}

static Node *insert(Node *root, int key)
{
    if (root == NULL) {
        return create_node(key);
    }

    if (key < root->key) {
        root->left = insert(root->left, key);
    } else if (key > root->key) {
        root->right = insert(root->right, key);
    } else {
        return root;
    }

    root->height = 1 + maximum(height(root->left), height(root->right));

    int balance = balance_factor(root);
    if (balance > 1 && key < root->left->key) {
        return rotate_right(root);
    }
    if (balance < -1 && key > root->right->key) {
        return rotate_left(root);
    }
    if (balance > 1 && key > root->left->key) {
        root->left = rotate_left(root->left);
        return rotate_right(root);
    }
    if (balance < -1 && key < root->right->key) {
        root->right = rotate_right(root->right);
        return rotate_left(root);
    }

    return root;
}

static const Node *search(const Node *root, int key)
{
    while (root != NULL && root->key != key) {
        root = key < root->key ? root->left : root->right;
    }
    return root;
}

static void print_in_order(const Node *root)
{
    if (root != NULL) {
        print_in_order(root->left);
        printf("%d ", root->key);
        print_in_order(root->right);
    }
}

static void free_tree(Node *root)
{
    if (root != NULL) {
        free_tree(root->left);
        free_tree(root->right);
        free(root);
    }
}

int main(void)
{
    const int keys[] = {10, 20, 30, 40, 50, 25};
    const size_t key_count = sizeof(keys) / sizeof(keys[0]);
    Node *root = NULL;

    for (size_t i = 0; i < key_count; i++) {
        root = insert(root, keys[i]);
    }

    printf("In-order traversal: ");
    print_in_order(root);
    putchar('\n');
    printf("Root after balancing: %d\n", root->key);
    printf("Search for 25: %s\n", search(root, 25) ? "found" : "not found");
    printf("Search for 99: %s\n", search(root, 99) ? "found" : "not found");

    free_tree(root);
    return 0;
}
