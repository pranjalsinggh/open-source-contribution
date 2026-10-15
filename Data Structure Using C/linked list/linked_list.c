#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

static int read_integer(const char *prompt, int *value)
{
    char input[128];
    char *end;
    long parsed;
    size_t length;

    printf("%s", prompt);
    if (fgets(input, sizeof input, stdin) == NULL) {
        return 0;
    }

    length = 0;
    while (input[length] != '\0' && input[length] != '\n') {
        length++;
    }
    if (input[length] == '\0' && !feof(stdin)) {
        int character;
        while ((character = getchar()) != '\n' && character != EOF) {
        }
        puts("Please enter a valid integer.");
        return -1;
    }

    errno = 0;
    parsed = strtol(input, &end, 10);
    if (end == input || errno == ERANGE || parsed < INT_MIN || parsed > INT_MAX) {
        puts("Please enter a valid integer.");
        return -1;
    }

    while (isspace((unsigned char)*end)) {
        end++;
    }
    if (*end != '\0') {
        puts("Please enter a valid integer.");
        return -1;
    }

    *value = (int)parsed;
    return 1;
}

static int append(Node **head, int value)
{
    Node *node = malloc(sizeof *node);
    Node **next;

    if (node == NULL) {
        perror("Unable to allocate a list node");
        return 0;
    }

    node->value = value;
    node->next = NULL;

    next = head;
    while (*next != NULL) {
        next = &(*next)->next;
    }
    *next = node;
    return 1;
}

static int delete_first(Node **head, int value)
{
    Node **current;
    Node *removed;

    for (current = head; *current != NULL; current = &(*current)->next) {
        if ((*current)->value == value) {
            removed = *current;
            *current = removed->next;
            free(removed);
            return 1;
        }
    }

    return 0;
}

static void display(const Node *head)
{
    if (head == NULL) {
        puts("The list is empty.");
        return;
    }

    printf("List: ");
    while (head != NULL) {
        printf("%d", head->value);
        head = head->next;
        if (head != NULL) {
            printf(" -> ");
        }
    }
    putchar('\n');
}

static void free_list(Node *head)
{
    while (head != NULL) {
        Node *next = head->next;
        free(head);
        head = next;
    }
}

int main(void)
{
    Node *head = NULL;
    int choice;
    int value;
    int result;

    for (;;) {
        puts("\n--- Singly linked list ---");
        puts("1. Add a value");
        puts("2. Delete the first matching value");
        puts("3. Display the list");
        puts("4. Exit");

        result = read_integer("Choice: ", &choice);
        if (result == 0) {
            break;
        }
        if (result < 0) {
            continue;
        }

        switch (choice) {
        case 1:
            result = read_integer("Value to add: ", &value);
            if (result == 0) {
                free_list(head);
                return 0;
            }
            if (result > 0) {
                append(&head, value);
            }
            break;
        case 2:
            result = read_integer("Value to delete: ", &value);
            if (result == 0) {
                free_list(head);
                return 0;
            }
            if (result > 0 && !delete_first(&head, value)) {
                puts("Value not found.");
            }
            break;
        case 3:
            display(head);
            break;
        case 4:
            free_list(head);
            return 0;
        default:
            puts("Please choose an option from 1 to 4.");
        }
    }

    free_list(head);
    return 0;
}
