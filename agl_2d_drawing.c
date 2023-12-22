#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef struct screen {
    char * sp;
    int height, width, size;
    char bgchar;
} screen_t;

typedef struct point {
    int x, y;
} point_t;

/*
typedef struct rect {
    int x, y, height, width;
} rect_t;

typedef struct polygon {
    point * points;
    int pointCount;
} polygon_t;

do we need shape types at the moment
*/

// `.-':_,^=;><+!rc*/z?sLTv)J7(|Fi{C}fI31tlu[neoZ5Yxjya]2ESwqkP6h9d4VpOGbUAKXHm8RD#$Bg0MNWQ%&@

static char lightValue[] = {' ', '`', '.', '-', '\'', ':', '_', ',', '^', '=', ';', '>', '<', '+', '!', 'r', 'c', '*', '/', 'z', '?', 's', 'L', 'T', 'v', ')', 'J', '7', '(', '|', 'F', 'i', '{', 'C', '}', 'f', 'I', '3', '1', 't', 'l', 'u', '[', 'n', 'e', 'o', 'Z', '5', 'Y', 'x', 'j', 'y', 'a', ']', '2', 'E', 'S', 'w', 'q', 'k', 'P', '6', 'h', '9', 'd', '4', 'V', 'p', 'O', 'G', 'b', 'U', 'A', 'K', 'X', 'H', 'm', '8', 'R', 'D', '#', '$', 'B', 'g', '0', 'M', 'N', 'W', 'Q', '%', '&', '@'};


screen_t screen_init(int width, int height, char bgchar) {
    screen_t screen;
    screen.height = height;
    screen.width = width;
    screen.size = height * width;
    screen.bgchar = bgchar;
    size_t size = width * height;
    screen.sp = (char*)malloc(size*sizeof(char)); 
    for(int i = 0; i < size; i++) {
	*(screen.sp + i) = bgchar;
    }
    return screen;
}

int convertX(int initX, int screenWidth) {
    return trunc((screenWidth/2) + initX);
}

int convertY(int initY, int screenHeight) {
    return trunc((screenHeight/2) - initY);
}

point_t convertPoint(point_t initPoint, int screenW, int screenH) {
    initPoint.x = trunc(screenW/2 + initPoint.x);
    initPoint.y = trunc(screenH/2 - initPoint.y);
    return initPoint;
}

void output(screen_t *screen) {
    for (int i = 0; i < screen->size; i++) {
	printf("%c", *(screen->sp + i));
	if ((i + 1) % screen->width == 0) {printf("\n");}
    } 
}

void clear(screen_t *screen) {
    for(int i = 0; i < screen->size; i++) {
	*(screen->sp + i) = screen->bgchar;	
    }
}

void drawPoint(screen_t *screen, int x, int y, char setChar) {
    x = convertX(x, screen->width);
    y = convertY(y, screen->height);
    if (x == screen->width | y == screen->height | x < 0 | y < 0) {
	printf("Out of bounds.\n");
	return;
    }
    int arrayPos = x + y * screen->width; 
    *(screen->sp + arrayPos) = setChar;
}

void drawPointL(screen_t *screen, int x, int y, int lightVal) {
    x = convertX(x, screen->width);
    y = convertY(y, screen->height);
    if (x == screen->width | y == screen->height | x < 0 | y < 0) {
		printf("Out of bounds.\n");
		return;
    }
    int arrayPos = x + y * screen->width; 
    *(screen->sp + arrayPos) = lightValue[lightVal];
}

void drawRect(screen_t *screen, int tlx, int tly, int brx, int bry, int fill, char setChar) {
    tlx = convertX(tlx, screen->width);
    tly = convertY(tly, screen->height);
    brx = convertX(brx, screen->width);
    bry = convertY(bry, screen->width);
    for (int i = tly; i <= bry; i++) {
	for (int i2 = tlx; i2 <= brx; i2++) {
	    if (!fill & (i == tly | i == bry | i2 == tlx | i2 == brx)) {
		drawPoint(screen, i2, i, setChar);
	    }
	    if (fill) {
		drawPoint(screen, i2, i, setChar);
	    }
	}
    }
}

void drawRectL(screen_t *screen, int tlx, int tly, int brx, int bry, int fill, int lightVal) {
    tlx = convertX(tlx, screen->width);
    tly = convertY(tly, screen->height);
    brx = convertX(brx, screen->width);
    bry = convertY(bry, screen->width);
    for (int i = tly; i <= bry; i++) {
		for (int i2 = tlx; i2 <= brx; i2++) {
			if (!fill & (i == tly | i == bry | i2 == tlx | i2 == brx)) {
				drawPointL(screen, i2, i, lightVal);
	    	}
	    	if (fill) {
				drawPointL(screen, i2, i, lightVal);
	    	}
		}
    }
}

void drawLine(screen_t *screen, int x0, int y0, int x1, int y1, char setChar) {
    x0 = convertX(x0, screen->width);
    y0 = convertY(y0, screen->height);
    x1 = convertX(x1, screen->width);
    y1 = convertY(y1, screen->height);
    printf("x0: %d\ny0: %d\nx1: %d\ny1: %d\n", x0, y0, x1, y1);
    int dx = x1 - x0;
    int dy = y1 - y0;
    int y = y0;
    int x = x0;
    if (abs(dy) < abs(dx)) {
	if (!(x0 < x1)) {
	    int buffer = x1; 
	    x1 = x0;
	    x0 = buffer;
	}
	int yi = 1;
	if (dy < 0) {
	    yi = -1;
	    dy = -dy;
	}
	int D = (2 * dy) - dx;
	printf("Initial D: %d\n", D);
	for (x = x0; x <= x1; x++) {
	    drawPoint(screen, x, y, setChar);
	    if (D > 0) {
		y = y + yi;
		D = D + (2 * (dy - dx));
	    } else {
		D = D + (2 * dy);
	    }
	}
    } else {
	if (!(y0 < y1)) {
	    int buffer = y1;
	    y1 = y0;
	    y0 = buffer;
	}	
	int xi = 1;
	if (dx < 0) {
	    xi = -1;
	    dx = -dx;
	}
	int D = (2 * dx) - dy;
	for (y = y0; y <= y1; y++) {
	    drawPoint(screen, x, y, setChar);
	    if (D > 0) {
		x = x + xi;
		D = D + (2 * (dx - dy));
	    } else {
		D = D + 2 * dx;
	    }
	}
    }
}

void drawLineL(screen_t *screen, int x0, int y0, int x1, int y1, int lightVal) {
    x0 = convertX(x0, screen->width);
    y0 = convertY(y0, screen->height);
    x1 = convertX(x1, screen->width);
    y1 = convertY(y1, screen->height);
    printf("x0: %d\ny0: %d\nx1: %d\ny1: %d\n", x0, y0, x1, y1);
    int dx = x1 - x0;
    int dy = y1 - y0;
    int y = y0;
    int x = x0;
    if (abs(dy) < abs(dx)) {
	if (!(x0 < x1)) {
	    int buffer = x1; 
	    x1 = x0;
	    x0 = buffer;
	}
	int yi = 1;
	if (dy < 0) {
	    yi = -1;
	    dy = -dy;
	}
	int D = (2 * dy) - dx;
	printf("Initial D: %d\n", D);
	for (x = x0; x <= x1; x++) {
	    drawPointL(screen, x, y, lightVal);
	    if (D > 0) {
		y = y + yi;
		D = D + (2 * (dy - dx));
	    } else {
		D = D + (2 * dy);
	    }
	}
    } else {
		if (!(y0 < y1)) {
			int buffer = y1;
			y1 = y0;
			y0 = buffer;
		}	
		int xi = 1;
		if (dx < 0) {
			xi = -1;
			dx = -dx;
		}
		int D = (2 * dx) - dy;
		for (y = y0; y <= y1; y++) {
			drawPointL(screen, x, y, lightVal);
			if (D > 0) {
				x = x + xi;
				D = D + (2 * (dx - dy));
			} else {
				D = D + 2 * dx;
			}
		}
    }
}

// NOTE: CHANGE ABOVE DRAW FUNCTIONS TO USE POINT_T INSTEAD OF INT
// CHANGE 
// keep old functions but append Raw
// never mind just use _Generic for function overloading lmao


void drawPolygon(screen_t *screen, point_t vertices[], int numOfVertices, char setChar) {
    for (int i = 0; i < numOfVertices; i++) {
	vertices[i] = convertPoint(vertices[i], screen->width, screen->height);
    } 
    for (int i = 0; i < numOfVertices; i++) {
	if (i < (numOfVertices - 1)) {
            printf("x1: %d\n y1: %d\n x2: %d\n y2: %d\n i: %d\n", vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i + 1].y, i);                      drawLine(screen, vertices[i].x, vertices[i].y, vertices[i+1].x, vertices[i + 1].y, setChar);
            output(screen);
        }
	if (i == (numOfVertices - 1)) {
	    printf("x1: %d\n y1: %d\n x2: %d\n y2: %d\n i: %d\n", vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, i);
	    drawLine(screen, vertices[i].x, vertices[i].y, vertices[0].x, vertices[0].y, setChar);
	    output(screen);
        }
    }
}
/*works but passsing parameters is buggy*/


