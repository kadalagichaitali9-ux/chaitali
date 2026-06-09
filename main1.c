#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 40
#define MAX_OBJECTS 100

typedef enum {
	SHAPE_RECTANGLE = 1,
	SHAPE_CIRCLE,
	SHAPE_LINE,
	SHAPE_TRIANGLE
} ShapeType;

typedef struct {
	int active;
	int id;
	ShapeType type;
	int p1;
	int p2;
	int p3;
	int p4;
	int p5;
	int p6;
} Shape;

char canvas[ROWS][COLS];
Shape shapes[MAX_OBJECTS];
int shapeCount = 0;

void initializeCanvas(void) {
	int i, j;
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			canvas[i][j] = '_';
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

void drawTriangle(int row1, int col1, int row2, int col2, int row3, int col3) {
	drawLine(row1, col1, row2, col2);
	drawLine(row2, col2, row3, col3);
	drawLine(row3, col3, row1, col1);
}

void displayCanvas(void) {
	int i, j;

	printf("\n");
	for (i = 0; i < ROWS; i++) {
		for (j = 0; j < COLS; j++) {
			printf("%c", canvas[i][j]);
		}
		printf("\n");
	}
}

void clearCanvas(void) {
	initializeCanvas();
}

void redrawPicture(void) {
	int i;

	clearCanvas();
	for (i = 0; i < shapeCount; i++) {
		if (!shapes[i].active) {
			continue;
		}

		if (shapes[i].type == SHAPE_RECTANGLE) {
			drawRectangle(shapes[i].p1, shapes[i].p2, shapes[i].p3, shapes[i].p4);
		} else if (shapes[i].type == SHAPE_CIRCLE) {
			drawCircle(shapes[i].p1, shapes[i].p2, shapes[i].p3);
		} else if (shapes[i].type == SHAPE_LINE) {
			drawLine(shapes[i].p1, shapes[i].p2, shapes[i].p3, shapes[i].p4);
		} else if (shapes[i].type == SHAPE_TRIANGLE) {
			drawTriangle(shapes[i].p1, shapes[i].p2, shapes[i].p3, shapes[i].p4, shapes[i].p5, shapes[i].p6);
		}
	}
}

void displayShapes(void) {
	int i;

	printf("\nCurrent objects:\n");
	for (i = 0; i < shapeCount; i++) {
		if (!shapes[i].active) {
			continue;
		}

		printf("ID %d: ", shapes[i].id);
		if (shapes[i].type == SHAPE_RECTANGLE) {
			printf("Rectangle at row %d col %d width %d height %d\n", shapes[i].p1, shapes[i].p2, shapes[i].p3, shapes[i].p4);
		} else if (shapes[i].type == SHAPE_CIRCLE) {
			printf("Circle at row %d col %d radius %d\n", shapes[i].p1, shapes[i].p2, shapes[i].p3);
		} else if (shapes[i].type == SHAPE_LINE) {
			printf("Line from (%d,%d) to (%d,%d)\n", shapes[i].p1, shapes[i].p2, shapes[i].p3, shapes[i].p4);
		} else if (shapes[i].type == SHAPE_TRIANGLE) {
			printf("Triangle (%d,%d) (%d,%d) (%d,%d)\n", shapes[i].p1, shapes[i].p2, shapes[i].p3, shapes[i].p4, shapes[i].p5, shapes[i].p6);
		}
	}
}

int addShape(Shape shape) {
	if (shapeCount >= MAX_OBJECTS) {
		return 0;
	}

	shape.active = 1;
	shape.id = shapeCount + 1;
	shapes[shapeCount] = shape;
	shapeCount++;
	return 1;
}

int findShapeIndexById(int id) {
	int i;

	for (i = 0; i < shapeCount; i++) {
		if (shapes[i].active && shapes[i].id == id) {
			return i;
		}
	}

	return -1;
}

void deleteShape(void) {
	int id;
	int index;
	int i;

	printf("Enter object ID to delete: ");
	scanf("%d", &id);

	index = findShapeIndexById(id);
	if (index == -1) {
		printf("Object not found.\n");
		return;
	}

	for (i = index; i < shapeCount - 1; i++) {
		shapes[i] = shapes[i + 1];
		shapes[i].id = i + 1;
	}

	shapeCount--;
	printf("Object deleted.\n");
}

void modifyShape(void) {
	int id;
	int index;
	Shape updated;

	printf("Enter object ID to modify: ");
	scanf("%d", &id);

	index = findShapeIndexById(id);
	if (index == -1) {
		printf("Object not found.\n");
		return;
	}

	printf("Select new shape type:\n");
	printf("1. Rectangle\n");
	printf("2. Circle\n");
	printf("3. Line\n");
	printf("4. Triangle\n");
	printf("Enter choice: ");
	scanf("%d", (int *)&updated.type);

	if (updated.type == SHAPE_RECTANGLE) {
		printf("Enter row, col, width, height: ");
		scanf("%d %d %d %d", &updated.p1, &updated.p2, &updated.p3, &updated.p4);
	} else if (updated.type == SHAPE_CIRCLE) {
		printf("Enter center row, center col, radius: ");
		scanf("%d %d %d", &updated.p1, &updated.p2, &updated.p3);
	} else if (updated.type == SHAPE_LINE) {
		printf("Enter row1, col1, row2, col2: ");
		scanf("%d %d %d %d", &updated.p1, &updated.p2, &updated.p3, &updated.p4);
	} else if (updated.type == SHAPE_TRIANGLE) {
		printf("Enter row1, col1, row2, col2, row3, col3: ");
		scanf("%d %d %d %d %d %d", &updated.p1, &updated.p2, &updated.p3, &updated.p4, &updated.p5, &updated.p6);
	} else {
		printf("Invalid shape type.\n");
		return;
	}

	updated.active = 1;
	updated.id = id;
	shapes[index] = updated;
	printf("Object modified.\n");
}

void addObject(void) {
	Shape shape;
	int choice;

	printf("Select shape type to add:\n");
	printf("1. Rectangle\n");
	printf("2. Circle\n");
	printf("3. Line\n");
	printf("4. Triangle\n");
	printf("Enter choice: ");
	scanf("%d", &choice);

	if (choice == SHAPE_RECTANGLE) {
		shape.type = SHAPE_RECTANGLE;
		printf("Enter row, col, width, height: ");
		scanf("%d %d %d %d", &shape.p1, &shape.p2, &shape.p3, &shape.p4);
	} else if (choice == SHAPE_CIRCLE) {
		shape.type = SHAPE_CIRCLE;
		printf("Enter center row, center col, radius: ");
		scanf("%d %d %d", &shape.p1, &shape.p2, &shape.p3);
	} else if (choice == SHAPE_LINE) {
		shape.type = SHAPE_LINE;
		printf("Enter row1, col1, row2, col2: ");
		scanf("%d %d %d %d", &shape.p1, &shape.p2, &shape.p3, &shape.p4);
	} else if (choice == SHAPE_TRIANGLE) {
		shape.type = SHAPE_TRIANGLE;
		printf("Enter row1, col1, row2, col2, row3, col3: ");
		scanf("%d %d %d %d %d %d", &shape.p1, &shape.p2, &shape.p3, &shape.p4, &shape.p5, &shape.p6);
	} else {
		printf("Invalid choice.\n");
		return;
	}

	if (!addShape(shape)) {
		printf("Picture is full. Cannot add more objects.\n");
		return;
	}

	printf("Object added with ID %d.\n", shapeCount);
}

void showMenu(void) {
	printf("\n2D GRAPHICS EDITOR\n");
	printf("1. Add object\n");
	printf("2. Delete object\n");
	printf("3. Modify object\n");
	printf("4. Display picture\n");
	printf("5. List objects\n");
	printf("6. Exit\n");
	printf("Enter choice: ");
}

int main(void) {
	int choice;

	initializeCanvas();

	while (1) {
		showMenu();
		scanf("%d", &choice);

		if (choice == 1) {
			addObject();
			redrawPicture();
			displayCanvas();
		} else if (choice == 2) {
			deleteShape();
			redrawPicture();
			displayCanvas();
		} else if (choice == 3) {
			modifyShape();
			redrawPicture();
			displayCanvas();
		} else if (choice == 4) {
			redrawPicture();
			displayCanvas();
		} else if (choice == 5) {
			displayShapes();
		} else if (choice == 6) {
			break;
		} else {
			printf("Invalid choice.\n");
		}
	}

	return 0;
}
