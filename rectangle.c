#include <stdio.h>

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

void drawRectangle(int row, int col, int width, int height) {
    int i;
    int bottom = row + height - 1;
    int right = col + width - 1;

    for (i = col; i <= right; i++) {
        plot(row, i);
        plot(bottom, i);
    }

    for (i = row; i <= bottom; i++) {
        plot(i, col);
        plot(i, right);
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
    int row;
    int col;
    int width;
    int height;

    initializeCanvas();

    printf("Enter row, col, width, height: ");
    if (scanf("%d %d %d %d", &row, &col, &width, &height) != 4) {
        return 1;
    }

    drawRectangle(row, col, width, height);
    displayCanvas();
    return 0;
}