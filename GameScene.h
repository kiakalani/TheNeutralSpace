#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "Scene.h"
void game_scene_init(scene_t*);
typedef enum
{
    POSITIVE, NEGATIVE, NEUTRAL
}game_space_t;
typedef struct enemy_adder_t
{
    float last_addition;
    float last_space_change;
    float next_space_change;
    uint16_t count_space_changes;
    game_space_t game_space;
}enemy_adder_t;
#endif