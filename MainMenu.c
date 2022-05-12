#include "MainMenu.h"
#include "Display.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Text.h"
#include "GameScene.h"

void __main_menu_handle_start_button(component_t *comp)
{
    if (glfwGetMouseButton(display->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        
        float mousex = display->mouse_x;
        float mousey = display->mouse_y;
        if (mousex > comp->position[0] - comp->scale[0] * 0.25f && mousex < comp->position[0] + comp->scale[0] * 0.25f)
        {
            if (mousey > comp->position[1] - comp->scale[1] * 0.75f - comp->scale[1] * 0.5f && mousey < comp->position[1] - comp->scale[1] * 0.75f )
            {
                scene_t *scene = (scene_t*)malloc(sizeof(scene_t));
                game_scene_init(scene);
                scene_t *del = display->current_scene;
                display->current_scene = scene;
                display->to_destroy = del;
                return;
            }
        }
    }

}

void __main_menu_handle_exit_button(component_t *comp)
{
    if (glfwGetMouseButton(display->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        
        float mousex = display->mouse_x;
        float mousey = display->mouse_y;
        if (mousex > comp->position[0] - comp->scale[0] * 0.25f && mousex < comp->position[0] + comp->scale[0] * 0.25f)
        {
            float ypos = comp->position[1] + comp->scale[1];
            if (mousey > ypos - comp->scale[1] && mousey < ypos )
            {
                glfwSetWindowShouldClose(display->window, 1);
                return;
            }
        }
    }
}

void __main_menu_add_exit_button(scene_t *s)
{
    component_t *exitbtn = (component_t*)malloc(sizeof(component_t));
    float button_color[] = {0.0f, 1.0f, 0.2f};
    text_init(exitbtn, "exit_button", "Quit Game", button_color);
    scene_add_component(s, exitbtn);
    exitbtn->position[1] = -0.5f;
    exitbtn->scale[0] = 0.5f;
    exitbtn->scale[1] = 0.25f;
    exitbtn->handle = __main_menu_handle_exit_button;
}

void __main_menu_add_start_button(scene_t *s)
{
    component_t *startbtn = (component_t*)malloc(sizeof(component_t));
    float button_color[] = {0.0f, 1.0f, 0.2f};
    text_init(startbtn, "start_button", "Start Game", button_color);
    scene_add_component(s, startbtn);
    startbtn->position[1] = 0.5f;
    startbtn->scale[0] = 0.5f;
    startbtn->scale[1] = 0.25f;
    startbtn->handle = __main_menu_handle_start_button;
}


void main_menu_init(scene_t *s)
{
    scene_init(s);
    __main_menu_add_start_button(s);
    __main_menu_add_exit_button(s);

}