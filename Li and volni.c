#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define ROW 8
#define COL 8
#define INF 9999

typedef struct {
    int x, y;
} Point;

bool isValid(int x, int y) {
    return (x >= 0 && x < ROW&& y >= 0 && y < COL);
}

void printPath(Point path[ROW][COL], Point end) {
    while (!(end.x == -1 && end.y == -1)) {
        printf("(%d, %d) ", end.x, end.y);
        end = path[end.x][end.y];
    }
    printf("\n");
}

void leeAlgorithm(int maze[ROW][COL], Point start, Point end) {
    int dr[] = { -1, 1, 0, 0 };
    int dc[] = { 0, 0, -1, 1 };

    int distance[ROW][COL];
    Point path[ROW][COL];

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            distance[i][j] = INF;
            path[i][j].x = -1;
            path[i][j].y = -1;
        }
    }

    distance[start.x][start.y] = 0;

    Point queue[ROW * COL];
    int front = 0, rear = 0;
    queue[rear++] = start;

    while (front < rear) {
        Point cur = queue[front++];

        for (int i = 0; i < 4; i++) {
            int nextX = cur.x + dr[i];
            int nextY = cur.y + dc[i];

            if (isValid(nextX, nextY) && maze[nextX][nextY] == 0 && distance[nextX][nextY] == INF) {
                distance[nextX][nextY] = distance[cur.x][cur.y] + 1;
                path[nextX][nextY] = cur;
                queue[rear].x = nextX;
                queue[rear].y = nextY;
                rear++;
            }
        }
    }

    if (distance[end.x][end.y] == INF) {
        printf("No path found.\n");
    }
    else {
        printf("Shortest path length: %d\n", distance[end.x][end.y]);
        printf("Shortest path: ");
        printPath(path, end);
    }
}

int main() {
    int maze[ROW][COL] = {
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 1, 1, 1, 0},
        {0, 0, 1, 0, 1, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0}
    };

    Point start = { 0, 0 };
    Point end = { 7, 7 };

    leeAlgorithm(maze, start, end);

    return 0;
}
