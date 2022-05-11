#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "Component.h"

typedef struct texture_components
{
    uint32_t texture_id;
}texture_components_t;

void texture_init(component_t*, const char*, const char*);
void texture_destroy(component_t*);

#endif