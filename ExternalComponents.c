#include "ExternalComponents.h"
#include "Texture.h"
#include "Buffer.h"
#include <stdlib.h>
#include <stdio.h>

void __external_components_ship_texture()
{
    component_t *ship_texture = (component_t*) malloc(sizeof(component_t));
    texture_init(ship_texture, "ship_texture", "../textures/ship.jpg");
    scene_add_component(display->external_comps, ship_texture);
    ship_texture = (component_t*)malloc(sizeof(component_t));
    texture_init(ship_texture, "enemy_texture", "../textures/enemy.png");
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
    comp = (component_t*)malloc(sizeof(component_t));
    buffer_create_cube(comp);
    scene_add_component(display->external_comps, comp);
    comp = (component_t*)malloc(sizeof(component_t));
    buffer_create_star(comp);
    scene_add_component(display->external_comps, comp);
}

void __external_components_load_shaders()
{
    shader_t *sh = (shader_t*)malloc(sizeof(shader_t));
    shader_init_shader(sh, "texture_shader", "../shaders/test/vert", "../shaders/test/frag");
    scene_add_shader(display->external_comps, sh);
}

void __external_components_load_text()
{
    shader_t *shader = (shader_t*)malloc(sizeof(shader_t));
    shader_init_shader(shader, "text_shader", "../shaders/text/vert", "../shaders/text/frag");
    scene_add_shader(display->external_comps, shader);
    char file_name[50];
    for (char i = 65; i < 91; ++i)
    {
        sprintf(file_name, "../textures/alphabets/%c.png", i);
        char name[10];
        sprintf(name, "%c_tex", i);
        component_t *texture = (component_t*)malloc(sizeof(component_t));
        texture_init(texture, (const char*)name, (const char*)file_name);
        scene_add_component(display->external_comps, texture);
    }
    for (char i = 97; i < 123; ++i)
    {
        sprintf(file_name, "../textures/alphabets/%c.png", i);
        char name[10];

        sprintf(name, "%c_tex", i);
        component_t *texture = (component_t*)malloc(sizeof(component_t));
        texture_init(texture, (const char*)name, (const char*)file_name);
        scene_add_component(display->external_comps, texture);
    }
    for (char i = 48; i < 58; ++i)
    {
        sprintf(file_name, "../textures/alphabets/%c.png", i);
        char name[10];
        sprintf(name, "%c_tex", i);
        component_t *texture = (component_t*)malloc(sizeof(component_t));
        texture_init(texture, (const char*)name, (const char*)file_name);
        scene_add_component(display->external_comps, texture);
    }
    sprintf(file_name, "../textures/alphabets/space.png");
    char name[10];
    sprintf(name, " _tex");
    component_t *texture = (component_t*)malloc(sizeof(component_t));
    texture_init(texture, (const char*)name, (const char*)file_name);
    scene_add_component(display->external_comps, texture);
}


void __external_components_health_bar()
{
    shader_t *health_shader = (shader_t*)malloc(sizeof(shader_t));
    shader_init_shader(health_shader, "health_shader", "../shaders/healthbar/vert", "../shaders/healthbar/frag");
    scene_add_shader(display->external_comps, health_shader);

    component_t *health_texture = (component_t*)malloc(sizeof(component_t));
    texture_init(health_texture, "health_texture", "../textures/health.png");
    scene_add_component(display->external_comps, health_texture);
}


void __external_components_screen_effect()
{
    shader_t *shader = (shader_t*)malloc(sizeof(shader_t));
    shader_init_shader(shader, "screen_shader", "../shaders/samplescreen/vert", "../shaders/samplescreen/frag");
    scene_add_shader(display->external_comps, shader);
}

void external_components_init()
{
    __external_components_ship_texture();
    __external_components_buffers();
    __external_components_load_shaders();
    __external_components_load_text();
    __external_components_health_bar();
    __external_components_screen_effect();
}