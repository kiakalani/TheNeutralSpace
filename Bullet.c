#include "Bullet.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Camera.h"
#include "LMath.h"
#include "Display.h"
#define DISAPPEARING_DISTANCE 500.0f
#define BULLET_SPEED 30.0f
static uint64_t __bullet_current_bullet = 0;

void __bullet_update(component_t *b)
{
    component_t *player = scene_get_component(display->current_scene, "player");
    float distance = lmath_distance(b->position, player->position, 3);
    if (distance > DISAPPEARING_DISTANCE)
    {
        scene_remove_component(display->current_scene, b);
        component_destroy(b);
        free(b);
        return;
    }

    // TODO: CHECK COLLISION DETECTION HERE
    bullet_components_t *bcomps = (bullet_components_t*)b->other_components;
    float pos_add[3];
    memcpy(pos_add, bcomps->forward, sizeof(float) * 3);
    lmath_multiply_vector_float(pos_add, bcomps->speed);
    lmath_add_vectors(b->position, pos_add);

}

void bullet_init(component_t *bullet, component_t *shooter)
{
    char bullet_name[30];
    sprintf(bullet_name, "bullet_%lu", __bullet_current_bullet++);
    component_init(bullet, (const char*)bullet_name);
    bullet->other_components = (void*)malloc(sizeof(bullet_components_t));
    bullet_components_t *bcomps = (bullet_components_t*)bullet->other_components;
    bullet->scale[0] = bullet->scale[1] = bullet->scale[2] = 0.1f;
    memset(bcomps, 0, sizeof(bullet_components_t));

    memcpy(bullet->position, shooter->position, sizeof(float) * 3);
    float fwd[3];
    memset(fwd, 0, sizeof(float) * 3);
    fwd[2] = -1.0f;
    camera_transform_vector_by_quat(shooter->orientation, fwd);
    fwd[1] = 1.0f + fwd[1];
    lmath_normalize(fwd, 3);
    
    
    memcpy(bcomps->forward, fwd, sizeof(float) * 3);

    bcomps->speed = BULLET_SPEED * display->delta_time;

    lmath_multiply_vector_float(fwd, 1.0f);
    lmath_add_vectors(bullet->position, fwd);

    bullet->update = __bullet_update;
    bullet->shader = scene_get_shader(display->external_comps, "texture_shader");
    lmath_print_vector(fwd, 3);
    component_add_component(bullet, scene_get_component(display->external_comps, "ship_texture"));
    component_add_component(bullet, scene_get_component(display->external_comps, "cube_buffer"));
}


