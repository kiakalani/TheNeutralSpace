#ifndef _TEXT_H_
#define _TEXT_H_
#include "Component.h"
typedef struct text_components
{
    char *text;
    float color[3];
}text_components_t;
void text_init(component_t*, const char*, const char*, float[3]);

void text_destroy(component_t*);
#endif