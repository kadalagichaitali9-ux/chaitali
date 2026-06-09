#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

void initializeCanvas(void) {
    int row;
    int col;

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            canvas[row][col] = '_';
        }
    }
}

void plot(int row, int col) {
    if (row >= 0 && row < ROWS && col >= 0 && col < COLS) {
        canvas[row][col] = '*';
    }
}

void drawLine(int row1, int col1, int row2, int col2) {
    int dx = abs(col2 - col1);
    int dy = abs(row2 - row1);
    int sx = (col1 < col2) ? 1 : -1;
    int sy = (row1 < row2) ? 1 : -1;
    int err = dx - dy;

    while (1) {
        plot(row1, col1);
        if (row1 == row2 && col1 == col2) {
            break;
        }

        if (2 * err > -dy) {
            err -= dy;
            col1 += sx;
        }

        if (2 * err < dx) {
            err += dx;
            row1 += sy;
        }
    }
}

void displayCanvas(void) {
    int row;
    int col;

    for (row = 0; row < ROWS; row++) {
        for (col = 0; col < COLS; col++) {
            printf("%c", canvas[row][col]);
        }
        printf("\n");
    }
}

int main(void) {
    int row1;
    int col1;
    int row2;
    int col2;

    initializeCanvas();

    printf("Enter row1, col1, row2, col2: ");
    if (scanf("%d %d %d %d", &row1, &col1, &row2, &col2) != 4) {
        return 1;
    }

    drawLine(row1, col1, row2, col2);
    displayCanvas();
    return 0;
}