#include "ExternalComponents.h"
#include "Texture.h"
#include "Buffer.h"
#include <stdlib.h>

void __external_components_ship_texture()
{
    component_t *ship_texture = (component_t*) malloc(sizeof(component_t));
    texture_init(ship_texture, "ship_texture", "../textures/ship.jpg");
    scene_add_component(display->external_comps, ship_texture);
}

void __external_components_buffers()
{
    component_t *comp = (component_t*)malloc(sizeof(component_t));
    buffer_create_quad(comp);
    scene_add_component(display->external_comps, comp);
    comp = (component_t*) malloc(sizeof(component_t));
    buffer_create_ship(comp);
    scene_add_component(display->external_comps, comp);
}

void external_components_init()
{
    __external_components_ship_texture();
    __external_components_buffers();
}