typedef struct screen {
    char * sp;
    int height, width, size;
    char bgchar;
} screen_t;

typedef struct point {
    int x, y;
} point_t;

screen_t screen_init(int width, int height, char bgchar);
void output(screen_t *screen);
void clear(screen_t *screen);
void drawPoint(screen_t *screen, int x, int y, char setChar);
void drawRect(screen_t *screen, int tlx, int tly, int brx, int bry, int fill, char setChar);
void drawLine(screen_t *screen, int x0, int y0, int x1, int y1, char setChar);
void drawPolygon(screen_t *screen, point_t vertices[], int numOfVertices, char setChar);
