#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "agl_2d_drawing.h"
#include "agl_3d_rendering.h"
#define inf 30000000

int main() {
    
    int sphereCount = 3;
    char color = ' ';
    printf("Input number of spheres you would like to render: ");
    scanf(" %d", &sphereCount);
    printf("Input background color (character) of the scene: ");
    scanf(" %c", &color);
    scene_t myScene = initScene(sphereCount, color);

    //  verifies if the initializer works
    for (int i = 0; i < myScene.sphereCount; i++) {
	printf("Sphere %d color: %c\n", i, (myScene.spheres + i)->color); 
	printf("Sphere %d radius: %f\n", i, (myScene.spheres + i)->radius);
	printf("Sphere %d center: %f, %f, %f\n", i, (myScene.spheres + i)->center.x, (myScene.spheres + i)->center.y, (myScene.spheres + i)->center.z);
    }
    int sx, sy, sz, r;
    for (int i = 0; i < myScene.sphereCount; i++) {
	printf("Input color (character) of sphere %d: ", i);
	scanf(" %c", &color);
	printf("Input x value of sphere %d: ", i);
	scanf("%f", &sx);
	printf("You typed in: %f\n", sx);
	printf("Input y value of sphere %d: ", i);
	scanf("%f", &sy);
	printf("You typed in: %f\n", sy);
	printf("Input z value of sphere %d: ", i);
	scanf("%f", &sz);
	printf("You typed in: %f\n", sz);
	printf("Input radius of sphere %d: ", i);
	scanf("%f", &r);
	printf("You typed in: %f\n", r);
	(myScene.spheres + i)->center = vectCopy(((myScene.spheres + i)->center), sx, sy, sz);
	(myScene.spheres + i)->color = color;
	(myScene.spheres + i)->radius = r;
    }
    
    // sample scene i used for testing
    (myScene.spheres + 0)-> center = vectCopy(((myScene.spheres + 0)->center), 0, -1, 3);
    (myScene.spheres + 0)->color = 'X';
    
    (myScene.spheres + 1)-> center = vectCopy(((myScene.spheres + 1)->center), 2, 0, 4);
    (myScene.spheres + 1)->color = '[';

    (myScene.spheres + 2)-> center = vectCopy(((myScene.spheres + 2)->center), -2, 0, 4);
    (myScene.spheres + 2)->color = '*';

    // verifies if values were changed properly
    printf("Values changed.\n");
    for (int i = 0; i < myScene.sphereCount; i++) {
	printf("Sphere %d color: %c\n", i, (myScene.spheres + i)->color); 
	printf("Sphere %d radius: %f\n", i, (myScene.spheres + i)->radius);
	printf("Sphere %d center: %f, %f, %f\n", i, (myScene.spheres + i)->center.x, (myScene.spheres + i)->center.y, (myScene.spheres + i)->center.z);
    }
    
    vec3_t origin = {0, 0, 0};
    vec3_t direction = {0, 0, 0};

    /*
    // verifies the interesction algorithm
    printf("select a sphere:\n");
    int i;
    scanf(" %d", &i);
    printf("Intersection test: %f\n", rsIntersect(origin, direction, (myScene.spheres + i)));
    
    int exit = 0;
    while (exit != 1) {
	printf("Raytrace test: \n"); 
	printf("x: ");
	scanf(" %f", &direction.x);
	printf("y: ");
	scanf(" %f", &direction.y);
	direction.z = 1;

	printf("Resulting Color: %c\n", traceRay(origin, direction, &myScene, inf, 1.0));
	printf("Exit? ");
	scanf(" %d", &exit);
	printf("\n\n");
    }
    */
    
    int screenWidth, screenHeight;
    char bgChar = '0';  
    printf("Input screen width: ");
    scanf("%d", &screenWidth);
    printf("Input screen height: ");
    scanf("%d", &screenHeight);

    int leftMostPos = -1 * trunc(screenWidth/2);
    int rightMostPos = screenWidth/2;
    int topMostPos = screenHeight/2;
    int bottomMostPos = -1 * screenHeight/2;
    printf("LMP: %d RMP: %d TMP: %d BMP: %d\n", leftMostPos, rightMostPos, topMostPos, bottomMostPos);

    screen_t myScreen = screen_init(screenWidth, screenHeight, bgChar);

    int viewportW = 2, viewportH = 2, viewportD = 1;
    viewport_t myViewport = {viewportW, viewportH, viewportD};

    char charToDraw;
    
    for (int x = leftMostPos; x <= rightMostPos; x++) {
	for (int y = bottomMostPos; y <= topMostPos; y++) {
	    printf("\nScreen Values: \nx: %d\ny: %d\n", x, y);
	    // this works
	    direction = screenToViewport(x, y, myViewport, screenWidth, screenHeight);
	    printf("\nDirection:\n");
	    printVect(&direction);
	    printf("\n");
	    
	    // i will review this
	    // weird thing to note: i never get a positive discriminant
	    charToDraw = traceRay(origin, direction, &myScene, inf, 1.0);
	    printf("Raytrace result: %c\n", charToDraw);
	    drawPoint(&myScreen, x, y, charToDraw);
	}
    }
    output(&myScreen);
    free(myScreen.sp);
    free(myScene.spheres);
    return 0;
}
