#ifndef _SCENE_H_
#define _SCENE_H_
#include "Component.h"
#include "Shader.h"
#include <stdint.h>
typedef struct scene
{
    component_t **components;
    uint64_t count_components, components_size;
    shader_t **shaders;
    uint64_t count_shaders, shaders_size;
    component_t *camera;
}scene_t;

// TODO: SEEMS TO BE FULLY IMPLEMENTED
void scene_init(scene_t*);
void scene_add_component(scene_t*, component_t*);
void scene_remove_component(scene_t*, component_t*);
void scene_remove_component_index(scene_t*, uint64_t);
component_t* scene_get_component(scene_t*, const char*);
void scene_iterate_components(scene_t*);
void scene_destroy(scene_t*);

void scene_add_shader(scene_t*, shader_t*);
shader_t *scene_get_shader(scene_t*, const char*);


void scene_check_collisions(scene_t*);

#endif