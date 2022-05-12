#include "GameOver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Display.h"
#include "MainMenu.h"
#include "Text.h"

void __game_over_init_text(scene_t *s, char w)
{
    component_t *component = (component_t*)malloc(sizeof(component_t));
    float color[] = {0.0f, 1.0f, 0.2f};
    text_init(component, "gover_message", w ? "REACHED NEUTRAL SPACE" : "YOU LOSE", color);
    component->scale[1] = 0.5f;
    scene_add_component(s, component);
}

void __game_over_handle_main_menu_button(component_t *comp)
{
    if (glfwGetMouseButton(display->window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        
        float mousex = display->mouse_x;
        float mousey = display->mouse_y;
        if (mousex < -0.25f && mousex > -0.5f)
        {
            if (mousey < -0.25f && mousey > -0.5f)
            {
                scene_t *s = (scene_t*)malloc(sizeof(scene_t));
                main_menu_init(s);
                scene_t *del = display->current_scene;
                display->current_scene = s;
                display->to_destroy = del;
            }
        }
    }
}

void __game_over_add_main_menu_button(scene_t *s)
{
    component_t *main_menu_btn = (component_t*)malloc(sizeof(component_t));
    float color[] = {0.0f, 1.0f, 0.2f};

    text_init(main_menu_btn, "main_menu_button", "Main Menu", color);
    main_menu_btn->position[0] = -0.75f;
    main_menu_btn->position[1] = -0.75f;
    main_menu_btn->scale[0] = 0.3f;
    main_menu_btn->scale[1] = 0.15f;
    scene_add_component(s, main_menu_btn);
    main_menu_btn->handle = __game_over_handle_main_menu_button;
}

void game_over_init(scene_t *s, char win)
{
    scene_init(s);
    __game_over_init_text(s, win);
    __game_over_add_main_menu_button(s);
}