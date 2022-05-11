#ifndef _DISPLAY_H_
#define _DISPLAY_H_
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdint.h>
#include "Scene.h"
typedef struct display
{
    GLFWwindow *window;
    uint16_t width, height;
    char *name;

    double mouse_x, mouse_y;

    scene_t *current_scene;
    scene_t *external_comps;
    double last_tick;
    double delta_time;
}display_t;

void display_init(display_t*, const uint16_t, const uint16_t, const char *);
void display_destroy(display_t*);

void display_loop(display_t*);
// DONE TESTED

extern display_t *display;


#endif