#ifndef _PLAYER_H_
#define _PLAYER_H_
#include "Component.h"
typedef struct player_components
{
    uint8_t space_pressed;
    float health, max_health;
    uint32_t count_bullets;
}player_components_t;

void player_init(component_t*);


#endif