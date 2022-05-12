#include "Display.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Buffer.h"
#include "Texture.h"
#include "Camera.h"
#include "LMath.h"
#include "ExternalComponents.h"
#include "Player.h"
#include "Text.h"
#include "Enemy.h"
#include "GameScene.h"
#include <time.h>
display_t *display;
void __display_resize(GLFWwindow *window, int w, int h)
{
    display_t *display = (display_t*)glfwGetWindowUserPointer(window);
    display->width = w;
    display->height = h;
    glViewport(0, 0, w, h);
}

void __display_cursor_callback(GLFWwindow *window, double x, double y)
{
    display_t *display = (display_t*)glfwGetWindowUserPointer(window);
    display->mouse_x = (x / (double)display->width) - 0.5;
    display->mouse_y = -((y / (double)display->height) - 0.5);
}

void __display_setup(display_t *display)
{
    if (!glfwInit())
    {
        display_destroy(display);
        printf("Error setting up GLFW\n");
        exit(0);
    }
    display->window = glfwCreateWindow(display->width, display->height, display->name, NULL, NULL);
    if (!display->window)
    {
        glfwTerminate();
        display_destroy(display);
        printf("Error setting up Window\n");
        exit(0);
    }

    glfwMakeContextCurrent(display->window);
    glewExperimental = 1;
    if (glewInit() != GLEW_OK)
    {
        glfwTerminate();
        display_destroy(display);
        printf("Error setting up GLEW\n");
        exit(0);
    }

    glEnable(GL_DEPTH_TEST);
    glEnable( GL_DEPTH_CLAMP ) ;
    glDepthFunc(GL_LESS);
    glViewport(0, 0, display->width, display->height);
    
    glfwSetWindowUserPointer(display->window, (void*)display);
    glfwSetFramebufferSizeCallback(display->window, __display_resize);
    glfwSetCursorPosCallback(display->window, __display_cursor_callback);
}


void display_init(display_t *display, const uint16_t w, const uint16_t h, const char *name)
{
    memset(display, 0, sizeof(display_t));
    display->width = w;
    display->height = h;
    display->name = (char*)calloc(sizeof(char), (strlen(name) + 1));
    char *n = display->name;
    for (char *i = (char*)name; *i != 0; ++i) *n++ = *i;
    __display_setup(display);

    display->external_comps = (scene_t*)malloc(sizeof(scene_t));
    scene_init(display->external_comps);
    external_components_init();
    float color[3] = {0.0f, 0.0f, 0.0f};
    memcpy(display->background, color, sizeof(float) * 3);
}


void display_loop(display_t *display)
{
    while (!glfwWindowShouldClose(display->window))
    {
        double cur_time = glfwGetTime();

        display->delta_time = cur_time - display->last_tick;
        if (display->delta_time <= 0.0f) display->delta_time = 0.002;
        
        glClearColor(display->background[0], display->background[1], display->background[2], 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                scene_check_collisions(display->current_scene);

        scene_iterate_components(display->current_scene);
        glfwPollEvents();

        glfwSwapBuffers(display->window);
        display->last_tick = cur_time;

        
        
    }
}


void display_destroy(display_t *display)
{
    free(display->name);
    if (display->current_scene) 
    {
        scene_destroy(display->current_scene);
        free(display->current_scene);
    }
    
    scene_destroy(display->external_comps);
    free(display->external_comps);

    glfwDestroyWindow(display->window);
    glfwTerminate();
}


void __sample_collision(component_t *first, component_t *second)
{

    scene_remove_component(display->current_scene, first);
    component_destroy(first);
    free(first);

}


int main()
{
    srand(time(NULL));
    display_t d;
    display = &d;
    display_init(&d, 1024, 768, "This is a test");
    scene_t *scene = (scene_t*)malloc(sizeof(scene_t));
    game_scene_init(scene);
    d.current_scene = scene;

    display_loop(&d);
    display_destroy(&d);

    return 0;
}