#ifndef inf
#define inf 30000000 
#endif
	
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

typedef struct scene {
    int sphereCount;
    char bgChar;
    sphere_t *spheres;
} scene_t;

float dot(vec3_t vector1, vec3_t vector2);
float vectLength(vec3_t vector);
vec3_t vectScalarMult(vec3_t vector, float mult);
vec3_t vectNormalize(vec3_t vector);
vec3_t vectSub(vec3_t vector1, vec3_t vector2);
vec3_t vectCopy(vec3_t vector, float x, float y, float z);
void printVect(vec3_t *vector); 

int sphereCompare(sphere_t sphere1, sphere_t sphere2);
vec3_t screenToViewport(int x, int y, viewport_t viewport, int screenW, int screenH);
scene_t initScene(int sphereCount, char bgChar);
float rsIntersect(vec3_t origin, vec3_t direction, sphere_t* sphere);
char traceRay(vec3_t origin, vec3_t direction, scene_t *scene, float maxT, float minT);
	
	
