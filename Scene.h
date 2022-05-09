#ifndef _SCENE_H_
#define _SCENE_H_
#include "Component.h"
#include <stdint.h>
typedef struct scene
{
    component_t **components;
    uint64_t count_components, components_size;
    component_t *camera;
}scene_t;

// TODO: SEEMS TO BE FULLY IMPLEMENTED
void scene_init(scene_t*);
void scene_add_component(scene_t*, component_t*);
void scene_remove_component(scene_t*, component_t*);
void scene_remove_component_index(scene_t*, uint64_t);

void scene_iterate_components(scene_t*);
void scene_destroy(scene_t*);


#endif