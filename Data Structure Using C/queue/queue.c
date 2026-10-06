#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QUEUE_CAPACITY 5
#define INPUT_SIZE 128

typedef struct
{
    int values[QUEUE_CAPACITY];
    size_t front;
    size_t rear;
    size_t size;
} CircularQueue;

static int read_integer(const char *prompt, int *value)
{
    char input[INPUT_SIZE];
    char *end;
    long parsed_value;
    size_t length;

    printf("%s", prompt);
    if (fgets(input, sizeof input, stdin) == NULL)
    {
        return 0;
    }

    length = strlen(input);
    if (length > 0 && input[length - 1] != '\n' && !feof(stdin))
    {
        int character;

        while ((character = getchar()) != '\n' && character != EOF)
        {
        }

        return 0;
    }

    errno = 0;
    parsed_value = strtol(input, &end, 10);
    if (end == input || errno == ERANGE || parsed_value < INT_MIN || parsed_value > INT_MAX)
    {
        return 0;
    }

    while (isspace((unsigned char)*end))
    {
        end++;
    }

    if (*end != '\0')
    {
        return 0;
    }

    *value = (int)parsed_value;
    return 1;
}

static void enqueue(CircularQueue *queue, int value)
{
    if (queue->size == QUEUE_CAPACITY)
    {
        puts("Queue is full.");
        return;
    }

    queue->values[queue->rear] = value;
    queue->rear = (queue->rear + 1) % QUEUE_CAPACITY;
    queue->size++;
    printf("Enqueued %d.\n", value);
}

static void dequeue(CircularQueue *queue)
{
    if (queue->size == 0)
    {
        puts("Queue is empty.");
        return;
    }

    printf("Dequeued %d.\n", queue->values[queue->front]);
    queue->front = (queue->front + 1) % QUEUE_CAPACITY;
    queue->size--;
}

static void display(const CircularQueue *queue)
{
    size_t i;

    if (queue->size == 0)
    {
        puts("Queue is empty.");
        return;
    }

    printf("Front -> ");
    for (i = 0; i < queue->size; i++)
    {
        size_t index = (queue->front + i) % QUEUE_CAPACITY;

        printf("%d", queue->values[index]);
        if (i + 1 < queue->size)
        {
            printf(" -> ");
        }
    }
    puts(" <- Rear");
}

int main(void)
{
    CircularQueue queue = {{0}, 0, 0, 0};
    int choice;

    for (;;)
    {
        puts("\n---- Circular Queue ----");
        puts("1. Enqueue");
        puts("2. Dequeue");
        puts("3. Display");
        puts("4. Exit");

        if (!read_integer("Enter your choice: ", &choice))
        {
            if (feof(stdin))
            {
                break;
            }

            puts("Invalid input. Enter a whole number.");
            continue;
        }

        switch (choice)
        {
            case 1:
            {
                int value;

                if (!read_integer("Enter a value: ", &value))
                {
                    if (feof(stdin))
                    {
                        return 0;
                    }

                    puts("Invalid input. Enter a whole number.");
                    break;
                }

                enqueue(&queue, value);
                break;
            }
            case 2:
                dequeue(&queue);
                break;
            case 3:
                display(&queue);
                break;
            case 4:
                return 0;
            default:
                puts("Invalid choice. Choose an option from 1 to 4.");
        }
    }

    return 0;
}
