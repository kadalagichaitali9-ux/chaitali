#include <stdio.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

void initializeCanvas() {
    int i, j;
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

void drawRectangle(int row, int col, int width, int height) {
    int i;

    for(i = col; i < col + width && i < COLS; i++) {
        canvas[row][i] = '*';

        if(row + height - 1 < ROWS)
            canvas[row + height - 1][i] = '*';
    }

    for(i = row; i < row + height && i < ROWS; i++) {
        canvas[i][col] = '*';

        if(col + width - 1 < COLS)
            canvas[i][col + width - 1] = '*';
    }
}

void displayCanvas() {
    int i, j;

    printf("\n");
    for(i = 0; i < ROWS; i++) {
        for(j = 0; j < COLS; j++) {
            printf("%c", canvas[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int row, col, width, height;

    initializeCanvas();

    printf("RECTANGLE DRAWING PROGRAM\n");

    printf("Enter starting row: ");
    scanf("%d", &row);

    printf("Enter starting column: ");
    scanf("%d", &col);

    printf("Enter width: ");
    scanf("%d", &width);

    printf("Enter height: ");
    scanf("%d", &height);

    drawRectangle(row, col, width, height);

    printf("\nRectangle Drawn Successfully!\n");

    displayCanvas();

    return 0;
}