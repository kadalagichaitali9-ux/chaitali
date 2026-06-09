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

void drawCircle(int centerRow, int centerCol, int radius) {
    int x = radius;
    int y = 0;
    int err = 0;

    while (x >= y) {
        plot(centerRow + y, centerCol + x);
        plot(centerRow + x, centerCol + y);
        plot(centerRow + x, centerCol - y);
        plot(centerRow + y, centerCol - x);
        plot(centerRow - y, centerCol - x);
        plot(centerRow - x, centerCol - y);
        plot(centerRow - x, centerCol + y);
        plot(centerRow - y, centerCol + x);

        y++;
        if (err <= 0) {
            err += 2 * y + 1;
        } else {
            x--;
            err += 2 * (y - x) + 1;
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
    int centerRow;
    int centerCol;
    int radius;

    initializeCanvas();

    printf("Enter center row, center col, radius: ");
    if (scanf("%d %d %d", &centerRow, &centerCol, &radius) != 3) {
        return 1;
    }

    drawCircle(centerRow, centerCol, radius);
    displayCanvas();
    return 0;
}