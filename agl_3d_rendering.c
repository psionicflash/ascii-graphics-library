#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "agl_2d_drawing.h"
#define inf 30000000
typedef struct viewport {
    int width, height, distance;
} viewport_t;

typedef struct vec3 {
    float x, y, z;
} vec3_t;

typedef struct sphere {
    vec3_t center;
    float radius;
    char color;
} sphere_t;

/*
typedef struct light {
  //0 = ambient, 1 = directional, 2 = point
  float type;
  float intensity;
  vec3_t position_direction;
} light_t;
*/

typedef struct scene {
    int sphereCount;
    //int lightCount;
    char bgChar;
    sphere_t *spheres;
    // light_t *lights;
} scene_t;

float dot(vec3_t vector1, vec3_t vector2) {
    return (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);
}

float vectLength(vec3_t vector) {
    return abs(sqrt((vector.x * vector.x) + (vector.y * vector.y) + (vector.z * vector.z)));
}

vec3_t vectSub(vec3_t vector1, vec3_t vector2) {
    vec3_t vector3;
    vector3.x = vector1.x - vector2.x;
    vector3.y = vector1.y - vector2.y;
    vector3.z = vector1.z - vector2.z;
    return vector3;
}

vec3_t vectScalarMult(vec3_t vector, float mult) {
    vector.x = vector.x * mult;
    vector.y = vector.y * mult;
    vector.z = vector.z * mult;
    return vector;
}

vec3_t vectNormalize(vec3_t vector) {
    float mult = vectLength(vector);
    mult = 1/mult;
    return vectScalarMult(vector, mult);
}

vec3_t vectCopy(vec3_t vector, float x, float y, float z) {
    vector.x = x;
    vector.y = y;
    vector.z = z;
    return vector;
}

int sphereCompare(sphere_t sphere1, sphere_t sphere2) {
   int result;
   if (sphere1.center.x == sphere2.center.x && sphere1.center.y == sphere2.center.y && sphere1.center.z == sphere2.center.z && sphere1.radius == sphere2.radius && sphere1.color == sphere2.color) {
       return 1;
   }
   return 0;
}

vec3_t screenToViewport(int x, int y, viewport_t viewport, int screenW, int screenH) {
    printf("viewport width: %d\n", viewport.width);
    printf("screen width: %d\n", screenW);
    printf("x: %d\n", x);
    float widthRatio = ((float) viewport.width/screenW);
    printf("width ratio: %f\n", widthRatio);
    float heightRatio = ((float) viewport.height/screenH);
    printf("height ratio: %f\n", heightRatio);
    float newX = x * ((float) viewport.width/screenW);
    printf("converted x: %f\n", newX);
    float newY = y * ((float) viewport.height/screenH);
    printf("y: %d\n", y);
    printf("converted y: %f", newY);
    vec3_t vector = {newX, newY, viewport.distance};
    return vector;
}

void printVect(vec3_t *vector) {
    printf("x: %f\ny: %f\nz: %f\n", vector->x, vector->y, vector->z);
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

    /*
    if (lightCount <= 0) {
      scene.lights = NULL;
    }
    */

    scene.spheres = (sphere_t*)malloc(sphereCount*sizeof(sphere_t));
    for (int i = 0; i < sphereCount; i++) {
      (scene.spheres + i)->radius = 1;
      printf("scene init test (radius): %f\n", (scene.spheres + i)->radius);
      (scene.spheres + i)->center = defaultVect;
      printf("scene init test (center):\n");
      printVect(&((scene.spheres + i)->center));
      (scene.spheres + i)->color = 'H';
      printf("scene init test (color): %c\n", (scene.spheres + i)->color);
    }

    /*
    scene.lights = (light_t*)malloc(lightCount*sizeof(light_t));
    for (int i = 0; i < lightCount; i++) {
      (scene.lights + i)->type = 0;
      (scene.lights + i)->intensity = 1.0;
      (scene.lights + i)->position_direction = defaultVect;
    }
    */

    return scene;
}

/*
float compLight(scene_t *scene, vec3_t point, vec3_t normal) {
    float intensity = 0.0;
    vec3_t lVect;
    float nlDot;
    for (int i = 0; i < scene->lightCount; i++) {
        if ((scene->lights + i)->type == 0) {
            intensity += (scene->lights + i)->intensity;
        } else { 
            if ((scene->lights + i)->type == 1) {
                lVect = (scene->lights + i)->position_direction;
            }
            if ((scene->lights + i)->type == 2) {
                lVect = vectSub((scene->lights + i)->position_direction, point);
            }
            nlDot = dot(normal, lVect);
            if (nlDot > 0) {
                intensity += (scene->lights + i)->intensity * nlDot/(vectLength(normal) * vectLength(lVect));
            }
        }
    }
    return intensity;
}
*/

float rsIntersect(vec3_t origin, vec3_t direction, sphere_t* sphere) {
    int tClosest = 2147483647;
    float radius = sphere->radius;
    vec3_t center = sphere->center; 
    //correct
    vec3_t ocDist = vectSub(origin, center);
    printf("direction: {%f, %f, %f}\n", direction.x, direction.y, direction.z);
    printf("center: {%f, %f, %f}\n", center.x, center.y, center.z);
    printf("origin: {%f, %f, %f}\n", origin.x, origin.y, origin.z);
    printf("ocDist: {%f, %f, %f}\n", ocDist.x, ocDist.y, ocDist.z);

    //correct
    float a = dot(direction, direction);
    //correct
    float b = 2 * dot(ocDist, direction);
    //correct
    float c = dot(ocDist, ocDist) - (radius * radius);
    printf("a: %f\nb: %f\nc: %f\n", a, b, c);


    float discriminant = ((b*b) - (4*a*c));
    printf("discriminant: %f\n", discriminant);
    if (discriminant < 0) {
	return inf;
    }
    
    
    float t1 = (-b + sqrt(discriminant))/(2*a);
    float t2 = (-b - sqrt(discriminant))/(2*a);
    printf("t1: %f\nt2: %f\n", t1, t2);

    if (t1 < t2) {
	printf("returning t1\n");
	return t1;
    }
    printf("returning t2\n");
    return t2;
} 

char traceRay(vec3_t origin, vec3_t direction, scene_t *scene, float maxT, float minT) {
    float closest_t = inf; 
    float t;
    sphere_t closest_sphere = {{inf,inf,inf}, -1, '\0'};
    sphere_t null_sphere = {{inf,inf,inf}, -1, '\0'};
    for (int i = 0; i < (scene->sphereCount); i++) {
      t = rsIntersect(origin, direction, (scene->spheres + i));
      printf("t: %f\n", t);
      if ((minT < t < maxT) && t < closest_t) {
          closest_t = t;
          printf("closest t: %f\n", closest_t);
          closest_sphere = *(scene->spheres + i);
      }
    }
    if (sphereCompare(closest_sphere,null_sphere) == 1) {
          return scene->bgChar;
    }
    return closest_sphere.color;
}


