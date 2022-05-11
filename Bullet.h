#ifndef _BULLET_H_
#define _BULLET_H_
#include "Component.h"
typedef struct bullet_components
{
    float speed;
    float forward[3];
    float power;
}bullet_components_t;
void bullet_init(component_t*, component_t*);


#endif