#include <stdio.h>

#define VERTEX_COUNT 6

static const int graph[VERTEX_COUNT][VERTEX_COUNT] = {
    {0, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 1, 0},
    {1, 0, 0, 0, 0, 1},
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 0, 0, 1},
    {0, 0, 1, 0, 1, 0}
};

static void breadth_first_search(int start)
{
    int queue[VERTEX_COUNT];
    int visited[VERTEX_COUNT] = {0};
    int front = 0;
    int rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    while (front < rear) {
        int vertex = queue[front++];

        printf("%d ", vertex);
        for (int neighbor = 0; neighbor < VERTEX_COUNT; neighbor++) {
            if (graph[vertex][neighbor] && !visited[neighbor]) {
                visited[neighbor] = 1;
                queue[rear++] = neighbor;
            }
        }
    }
    putchar('\n');
}

static void depth_first_search_visit(int vertex, int visited[VERTEX_COUNT])
{
    visited[vertex] = 1;
    printf("%d ", vertex);

    for (int neighbor = 0; neighbor < VERTEX_COUNT; neighbor++) {
        if (graph[vertex][neighbor] && !visited[neighbor]) {
            depth_first_search_visit(neighbor, visited);
        }
    }
}

static void depth_first_search(int start)
{
    int visited[VERTEX_COUNT] = {0};

    depth_first_search_visit(start, visited);
    putchar('\n');
}

int main(void)
{
    printf("BFS from vertex 0: ");
    breadth_first_search(0);

    printf("DFS from vertex 0: ");
    depth_first_search(0);

    return 0;
}
