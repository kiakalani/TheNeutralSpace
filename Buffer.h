#ifndef _BUFFER_H_
#define _BUFFER_H_
#include <stdint.h>
#include "Component.h"
typedef struct buffer_components
{   
    uint32_t vbo, ebo;
    uint32_t size_indices;
}buffer_components_t;


void buffer_init(component_t *buff, const char*, float *verts, uint64_t cverts, uint32_t *faces, uint64_t cfaces);
void buffer_destroy(component_t*);

void buffer_create_quad(component_t*);
void buffer_create_ship(component_t*);
void buffer_create_star(component_t*);
#endif