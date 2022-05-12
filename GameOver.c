#include "GameOver.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Text.h"

void __game_over_init_text(scene_t *s, char w)
{
    component_t *component = (component_t*)malloc(sizeof(component_t));
    float color[] = {0.0f, 1.0f, 0.2f};
    text_init(component, "gover_message", w ? "REACHED NEUTRAL SPACE" : "YOU LOSE", color);
    scene_add_component(s, component);
}

void game_over_init(scene_t *s, char win)
{
    __game_over_init_text(s, win);
}