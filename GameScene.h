#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_
#include "Scene.h"
void game_scene_init(scene_t*);
typedef enum
{
    POSITIVE, NEGATIVE, NEUTRAL
}game_space_t;
#endif