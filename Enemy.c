#include "Enemy.h"
#include <stdio.h>
#include "Display.h"
#include <stdlib.h>
#include <string.h>
#include "LMath.h"
#include "Bullet.h"
#include "Player.h"
#include "GameScene.h"
#define ENEMY_DAMAGE 2.0f
#define ENEMY_HEALTH 4.0f
#define ENEMY_MAXIMUM_DISTANCE 50.0f
#define ENEMY_ENEMY_SPEED 1.0f
static uint64_t __enemy_current_enemy = 0;

void __enemy_update(component_t *comp)
{
        component_t *player = scene_get_component(display->current_scene, "player");

    enemy_components_t *ecomps = (enemy_components_t*)comp->other_components;
    float distance = lmath_distance(comp->position, player->position, 3);
    if (distance > ENEMY_MAXIMUM_DISTANCE || ecomps->health <= 0.0f)
    {
        if (ecomps->health <= 0.0f)
        {
            player_components_t *pcomps = (player_components_t*)player->other_components;
            pcomps->count_bullets += 5;
        }
        scene_remove_component(display->current_scene, comp);
        component_destroy(comp);
        free(comp);
        return;
    }
    float forward[3];
    memcpy(forward, comp->position, sizeof(float) * 3);
    lmath_multiply_vector_float(forward, -1.0f);
    lmath_add_vectors(forward, player->position);
    lmath_normalize(forward, 3);


    lmath_multiply_vector_float(forward, ENEMY_ENEMY_SPEED * display->delta_time);
    lmath_add_vectors(comp->position, forward);


    float y_rot[4];
    lmath_angle_axis_quat( display->delta_time, 0.0f, 1.0f, 0.0f, y_rot);
    float result[4];
    lmath_quat_multiply(y_rot, comp->orientation, result);
    lmath_normalize(result, 4);
    memcpy(comp->orientation, result, sizeof(float) * 4);
    lmath_angle_axis_quat( display->delta_time, 0.0f, 0.0f, 1.0f, y_rot);
    lmath_quat_multiply(y_rot, comp->orientation, result);
    lmath_normalize(result, 4);
    memcpy(comp->orientation, result, sizeof(float) * 4);
    
    
}

void __enemy_on_collision(component_t *enemy, component_t *item)
{
    char negative = 0;
    enemy_adder_t *eadder = (enemy_adder_t*)scene_get_component(display->current_scene, "enemy_generator")->other_components;
    negative = eadder->game_space == NEGATIVE;
    char bullet[] = "bullet_";
    if (!memcmp(item->name, bullet, sizeof(bullet) - (sizeof(char))))
    {
        bullet_components_t *bcomps = (bullet_components_t*)item->other_components;

        if (negative)
        {
            player_components_t *pcomps = (player_components_t*)(scene_get_component(display->current_scene, "player")->other_components);
            pcomps->health -= bcomps->power;
        } else
        {
            enemy_components_t *ecomps = (enemy_components_t*)enemy->other_components;
            ecomps->health -= bcomps->power;
        }
        
    }
    else if (!strcmp(item->name, "player"))
    {
        player_components_t *pcomps = (player_components_t*)item->other_components;
        if (!negative)
        pcomps->health -= ((enemy_components_t*)(enemy->other_components))->damage;
        ((enemy_components_t*)(enemy->other_components))->health = -0.1f;
    }

}

void __enemy_set_random_position(component_t *e)
{
    component_t *player = scene_get_component(display->current_scene, "player");
    memcpy(e->position, player->position, sizeof(float) * 3);
    e->position[0] += (float)((rand() % 10) - 5);
    e->position[1] += (float)((rand() % 10) - 5);
    e->position[2] -= 45.0f;

}

void enemy_init(component_t *e)
{
    char name[30];
    sprintf(name, "enemy_%lu", __enemy_current_enemy++);
    component_init(e, (const char*)name);
    e->update = __enemy_update;
    component_add_component(e, scene_get_component(display->external_comps, "enemy_texture"));
    component_add_component(e, scene_get_component(display->external_comps, "star_buffer"));
    __enemy_set_random_position(e);
    e->on_collision = __enemy_on_collision;
    e->shader = scene_get_shader(display->external_comps, "texture_shader");
    e->other_components = (enemy_components_t*)calloc(sizeof(enemy_components_t), 1);
    enemy_components_t *ecomps = (enemy_components_t*)e->other_components;
    ecomps->damage = ENEMY_DAMAGE;
    ecomps->health = ENEMY_HEALTH;

}