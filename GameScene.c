#include "GameScene.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Display.h"
#include "Enemy.h"
#include "Player.h"
#include "Text.h"
#include "Health.h"
#define GAME_SCENE_ENEMY_TIME 10.0f
#define COUNT_CHANGES_TO_NEUTRAL 20



void __game_scene_update_enemy_generator(component_t *e)
{
    enemy_adder_t *ecomps = (enemy_adder_t*)e->other_components;
    if (glfwGetTime() - ecomps->last_addition > GAME_SCENE_ENEMY_TIME)
    {
        ecomps->last_addition = glfwGetTime();
        component_t *enemy = (component_t*) malloc(sizeof(component_t));
        enemy_init(enemy);
        scene_add_component(display->current_scene, enemy);
    }
    if (glfwGetTime() - ecomps->last_space_change > ecomps->next_space_change)
    {
        ecomps->next_space_change = 10.0f * ((rand() % 5) + 1);
        ecomps->count_space_changes++;
        ecomps->last_space_change = glfwGetTime();
        if (ecomps->game_space == NEGATIVE)
        {
            ecomps->game_space = POSITIVE;
        } else if (ecomps->game_space == POSITIVE) ecomps->game_space = NEGATIVE;

        if (ecomps->count_space_changes != 0 && ecomps->count_space_changes >= COUNT_CHANGES_TO_NEUTRAL)
        {
            ecomps->game_space = NEUTRAL;
        }
    }

    if (ecomps->game_space == NEUTRAL)
    {

        // Player wins the game and change the scene to show that
    }
    else if (ecomps->game_space == NEGATIVE)
    {
        float background[] = {0.4f, 0.0f, 0.0f};
        memcpy(display->background, background, sizeof(float) * 3);
    }
    else
    {
        memset(display->background, 0, sizeof(float) * 3);
    }


    component_t *player = scene_get_component(display->current_scene, "player");
    player_components_t *pcomps = (player_components_t*)player->other_components;
    if (pcomps->health < 0.0f)
    {
        // Change the scene and indicate that player loses.
    }
}

void __game_scene_add_enemy_generator(scene_t *s)
{
    component_t *comp = (component_t*)malloc(sizeof(component_t));
    component_init(comp, "enemy_generator");
    comp->render = NULL;
    comp->update = __game_scene_update_enemy_generator;
    enemy_adder_t *e_comps;
    comp->other_components =(void*) (e_comps = (enemy_adder_t*)calloc(sizeof(enemy_adder_t), 1));
    e_comps->last_addition = e_comps->last_space_change = glfwGetTime();
    e_comps->next_space_change = 10.0f * ((rand() % 5) + 1);
    scene_add_component(s, comp);
}


void __game_scene_add_player(scene_t *s)
{
    component_t *player = (component_t*)malloc(sizeof(component_t));
    player_init(player);
    scene_add_component(s, player);
}


void __game_scene_bullet_text_update(component_t *comp)
{
    component_t *player = scene_get_component(display->current_scene, "player");
    player_components_t *pcomps = (player_components_t*)player->other_components;
    char text[18];
    sprintf(text, "%u Bullets", pcomps->count_bullets);
    component_t *bull_txt = scene_get_component(display->current_scene, "bullet_text");
    text_components_t *t_comps = (text_components_t*)bull_txt->other_components;
    sprintf(t_comps->text, "%s", text);
}


void __game_scene_setup_bullet_text(scene_t *s)
{
    component_t *text = (component_t*)malloc(sizeof(component_t));
    char bullet_count[30];
    sprintf(bullet_count, "999999999 Bullets");
    float background[3] = {0.0f, 1.0f, 1.0f};
    text_init(text, "bullet_text", bullet_count, background);
    scene_add_component(s, text);
    text->update = __game_scene_bullet_text_update;
    
    text->scale[0] = 0.30f;
    text->scale[1] = 0.15f;
    text->position[0] = -0.75f;
    text->position[1] = -0.75f;
}

void __game_scene_add_initial_enemy()
{
    component_t *enemy = (component_t*) malloc(sizeof(component_t));
    enemy_init(enemy);
    scene_add_component(display->current_scene, enemy);
}


void __game_scene_add_health_bar(scene_t *s)
{
    component_t *health = (component_t*)malloc(sizeof(component_t));
    health_init(health);
    scene_add_component(s, health);
}


void __game_scene_add_screen_effect(scene_t *s)
{
    component_t *comp = (component_t*)malloc(sizeof(component_t));
    component_init(comp, "screen_effect");
    component_add_component(comp, scene_get_component(display->external_comps, "quad_buffer"));
    comp->shader = scene_get_shader(display->external_comps, "screen_shader");
    scene_add_component(s, comp);
}

void game_scene_init(scene_t *s)
{
    scene_init(s);
    scene_t *cur_scene = display->current_scene;
    display->current_scene = s;
    __game_scene_add_player(s);
    __game_scene_add_initial_enemy();

    display->current_scene = cur_scene;
    __game_scene_add_enemy_generator(s);
    __game_scene_setup_bullet_text(s);
    __game_scene_add_health_bar(s);
    __game_scene_add_screen_effect(s);
}