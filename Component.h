#ifndef _COMPONENT_H_
#define _COMPONENT_H_
#include <stdint.h>
#include "Shader.h"
typedef struct component
{
    float position[3];
    float scale[3];
    float orientation[4];
    void *other_components;
    struct component **components;
    uint64_t count_components, size_components;
    void (*render)(struct component*, shader_t*);
    void (*handle)(struct component*);
    void (*update)(struct component*);
    void (*destroy_other_comps)(struct component*);
    shader_t *shader;
}component_t;


void component_init(component_t*);
void component_destroy(component_t*);


void component_add_component(component_t*, component_t*);
void component_remove_component(component_t*, component_t*);
void component_remove_component_index(component_t*, uint64_t);
void component_destroy_components(component_t*);


void component_get_transformation_mat(component_t*, float*);

void component_face_component(component_t*, component_t*);



void component_forward_vec(component_t*, float[3]);
void component_side_vec(component_t*, float[3]);
void component_up_vec(component_t*, float[3]);

#endif