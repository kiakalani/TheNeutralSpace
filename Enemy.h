#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "Component.h"
typedef struct enemy_components
{
    float damage;
    float health;
}enemy_components_t;
void enemy_init(component_t*);
void enemy_on_collisioin(component_t*);

#endif