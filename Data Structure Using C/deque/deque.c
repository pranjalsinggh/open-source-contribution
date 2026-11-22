#include <stdio.h>

#define DEQUE_SIZE 5

int deque[DEQUE_SIZE];
int front = -1;
int rear = -1;

int is_empty(void)
{
    return front == -1;
}

int is_full(void)
{
    return ((front == 0 && rear == DEQUE_SIZE - 1) ||
            (front == rear + 1));
}

void insert_front(int value)
{
    if (is_full()) {
        printf("Deque is full\n");
        return;
    }

    if (is_empty()) {
        front = 0;
        rear = 0;
    } else if (front == 0) {
        front = DEQUE_SIZE - 1;
    } else {
        front--;
    }

    deque[front] = value;
}

void insert_rear(int value)
{
    if (is_full()) {
        printf("Deque is full\n");
        return;
    }

    if (is_empty()) {
        front = 0;
        rear = 0;
    } else if (rear == DEQUE_SIZE - 1) {
        rear = 0;
    } else {
        rear++;
    }

    deque[rear] = value;
}

int delete_front(void)
{
    int value;

    if (is_empty()) {
        printf("Deque is empty\n");
        return -1;
    }

    value = deque[front];
    if (front == rear) {
        front = -1;
        rear = -1;
    } else if (front == DEQUE_SIZE - 1) {
        front = 0;
    } else {
        front++;
    }

    return value;
}

int delete_rear(void)
{
    int value;

    if (is_empty()) {
        printf("Deque is empty\n");
        return -1;
    }

    value = deque[rear];
    if (front == rear) {
        front = -1;
        rear = -1;
    } else if (rear == 0) {
        rear = DEQUE_SIZE - 1;
    } else {
        rear--;
    }

    return value;
}

void display(void)
{
    int i;

    if (is_empty()) {
        printf("Deque is empty\n");
        return;
    }

    printf("Deque: ");
    i = front;
    while (1) {
        printf("%d ", deque[i]);
        if (i == rear) {
            break;
        }
        i = (i + 1) % DEQUE_SIZE;
    }
    printf("\n");
}

int main(void)
{
    insert_rear(10);
    insert_rear(20);
    insert_front(5);
    insert_front(1);
    display();

    printf("Deleted from front: %d\n", delete_front());
    printf("Deleted from rear: %d\n", delete_rear());
    display();

    return 0;
}
