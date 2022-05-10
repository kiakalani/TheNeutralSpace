#include "Display.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "Buffer.h"
#include "Texture.h"
#include "Camera.h"
#include "LMath.h"
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

}
void __rotate_object(component_t *comp)
{
    // float orientation[4];
    // lmath_angle_axis_quat(0.01f, 1.0f, 0.0f, 0.0f, orientation);
    // float c_orientation[4];
    // memcpy(c_orientation, comp->orientation, sizeof(float) * 4);

    // lmath_quat_multiply(orientation, c_orientation, comp->orientation);
    // lmath_normalize(comp->orientation, 4);
    // lmath_print_vector(comp->orientation, 4);
    //comp->position[2] += 0.01f;
    //printf("WORKING\n");
    lmath_print_vector(comp->position, 3);
}

void display_loop(display_t *display)
{
    while (!glfwWindowShouldClose(display->window))
    {
        double cur_time = glfwGetTime();

        display->delta_time = cur_time - display->last_tick;
        if (display->delta_time <= 0.0f) display->delta_time = 0.002;
        
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
    glfwDestroyWindow(display->window);
    glfwTerminate();
}


int main()
{
    display_t d;
    display = &d;
    display_init(&d, 1024, 768, "This is a test");

    component_t test_tex;

    texture_init(&test_tex, "../textures/test.jpg");

    scene_t *scene = (scene_t*)malloc(sizeof(scene_t));
    scene_init(scene);
    d.current_scene = scene;
    shader_t test_shader;
    shader_init_shader(&test_shader, "../shaders/test/vert", "../shaders/test/frag");
    component_t test_buff;
    // buffer_create_quad(&test_buff);
    buffer_create_ship(&test_buff);
    component_t test2_buff;
    buffer_create_quad(&test2_buff);

    component_t *componen2 = (component_t*) malloc(sizeof(component_t));
    component_init(componen2);
    componen2->shader = &test_shader;
    component_add_component(componen2, &test_tex);
    component_add_component(componen2, &test2_buff);
    
    component_t *component = (component_t*)malloc(sizeof(component_t));
    component_init(component);
    component->shader = &test_shader;
    component_add_component(component, &test_buff);
    component_add_component(component, &test_tex);

    scene_add_component(scene, component);
    scene_add_component(scene, componen2);

    componen2->position[1] = 1.0f;

    shader_t scr_sh;
    shader_init_shader(&scr_sh, "../shaders/samplescreen/vert", "../shaders/samplescreen/frag");
    component_t *screen_eff = (component_t*)malloc(sizeof(component_t));
    component_init(screen_eff);
    screen_eff->shader = &scr_sh;
    component_add_component(screen_eff, &test2_buff);

    scene_add_component(scene, screen_eff);

    scene->camera->position[2] = 5.0f;
    camera_follow_object(scene->camera, component);
    componen2->update = __rotate_object;

    lmath_angle_axis_quat(-3.141522f * 0.2f, 1.0f, 0.0f, 0.0f, component->orientation);

    display_loop(&d);
    shader_destroy_shader(&test_shader);
    component_destroy(&test_buff);
    display_destroy(&d);

    component_destroy(&test_tex);
    component_destroy(&test2_buff);
    return 0;
}