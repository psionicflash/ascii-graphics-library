#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "agl_2d_drawing.h"
typedef struct viewport {
    int width, height, distance;
} viewport_t;

typedef struct vec3 {
    int x, y, z;
} vec3_t;

typedef struct sphere {
    vec3_t center;
    int radius;
    char color;
} sphere_t;

typedef struct scene {
    int sphereCount;
    char bgChar;
    sphere_t *spheres;
} scene_t;

int dot(vec3_t vector1, vec3_t vector2) {
    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

vec3_t vectSub(vec3_t vector1, vec3_t vector2) {
    vec3_t vector3;
    vector3.x = vector1.x - vector2.x;
    vector3.y = vector1.y - vector2.y;
    vector3.z = vector1.z - vector2.z;
    return vector3;
}

scene_t initScene(int sphereCount, char bgChar) {
    scene_t scene;
    vec3_t defaultVect = {0, 0, 0};
    scene.bgChar = bgChar;
    scene.sphereCount = sphereCount;

    if (sphereCount <= 0) {
	scene.spheres = NULL;
	return scene;
    }
    scene.spheres = (sphere_t*)malloc(sphereCount*sizeof(sphere_t));
    for (int i = 0; i < sphereCount; i++) {
	(scene.spheres + i)->radius = 1;
	(scene.spheres + i)->center = defaultVect;
	(scene.spheres + i)->color = 'H';
    }
    return scene;
}

int rsIntersect(vec3_t origin, vec3_t direction, sphere_t* sphere) {
    int tClosest = 4294967295;
    int radius = sphere->radius;
    vec3_t center = sphere->center; 
    vec3_t ocDist = vectSub(origin, center);
    printf("direction: {%d, %d, %d}\n", direction.x, direction.y, direction.z);
    printf("center: {%d, %d, %d}\n", center.x, center.y, center.z);
    printf("origin: {%d, %d, %d}\n", origin.x, origin.y, origin.z);
    printf("ocDist: {%d, %d, %d}\n", ocDist.x, ocDist.y, ocDist.z);

    int a = dot(direction, direction);
    int b = 2 * dot(ocDist, direction);
    int c = dot(ocDist, ocDist) - (radius * radius);
    printf("a: %d\nb: %d\nc: %d\n", a, b, c);


    int discriminant = b*b - 4*a*c;
    printf("discriminant: %d\n", discriminant);
    if (discriminant < 0) {
	return 429467295;
    }
    
    
    float t1 = (-b + sqrt(discriminant))/(2*a);
    float t2 = (-b - sqrt(discriminant))/(2*a);
    printf("t1: %f\nt2: %f\n", t1, t1);

    if (t1 < t2) {
	return t1;
    }

    return t2;
} 

int main() {
    scene_t myScene = initScene(3, 'x');
    for (int i = 0; i < myScene.sphereCount; i++) {
	printf("Sphere %d color: %c\n", i, (myScene.spheres + i)->color); 
	printf("Sphere %d radius: %d\n", i, (myScene.spheres + i)->radius);
	printf("Sphere %d center: %d, %d, %d\n", i, (myScene.spheres + i)->center.x, (myScene.spheres + i)->center.y, (myScene.spheres + i)->center.z);
    }
    
    (myScene.spheres + 0)->center.x = 0;
    (myScene.spheres + 0)->center.y = -1;
    (myScene.spheres + 0)->center.z = 3;
    (myScene.spheres + 0)->color = 'X';

    (myScene.spheres + 1)->center.x  = 2;
    (myScene.spheres + 1)->center.y  = 0;
    (myScene.spheres + 1)->center.z  = 4;
    (myScene.spheres + 1)->color = '[';

    (myScene.spheres + 2)->center.x = -2;
    (myScene.spheres + 2)->center.y = 0;
    (myScene.spheres + 2)->center.z = 4;
    (myScene.spheres + 2)->color = 'M';

    printf("Values changed.\n");

    for (int i = 0; i < myScene.sphereCount; i++) {
	printf("Sphere %d color: %c\n", i, (myScene.spheres + i)->color); 
	printf("Sphere %d radius: %d\n", i, (myScene.spheres + i)->radius);
	printf("Sphere %d center: %d, %d, %d\n", i, (myScene.spheres + i)->center.x, (myScene.spheres + i)->center.y, (myScene.spheres + i)->center.z);
    }

    vec3_t origin = {0, 0, 0};
    vec3_t direction = {-2, 0, 4};
    printf("select a sphere:\n");
    int i;
    scanf(" %d", &i);
    printf("Intersection test: %d", rsIntersect(origin, direction, (myScene.spheres + i)));

    return 0;
}


