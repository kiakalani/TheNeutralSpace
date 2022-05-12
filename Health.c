#include "Health.h"
#include "Display.h"
#include "Player.h"
extern void __component_sample_render(component_t*, shader_t*);

void __health_render(component_t *comp, shader_t *shader)
{
    component_t *player = scene_get_component(display->current_scene, "player");
    player_components_t *pcomps = (player_components_t*)player->other_components;
    float health_frac = pcomps->health / pcomps->max_health;
    glUniform1fv(glGetUniformLocation(shader->program_id, "health_frac"), 1, &health_frac);
    __component_sample_render(comp, shader);
}

void health_init(component_t *h)
{
    component_init(h, "health_bar");
    h->render = __health_render;
    component_add_component(h, scene_get_component(display->external_comps, "health_texture"));
    component_add_component(h, scene_get_component(display->external_comps, "quad_buffer"));
    h->shader = scene_get_shader(display->external_comps, "health_shader");
    h->position[1] = -0.75f;
    h->scale[1] = 0.15f;
    h->scale[0] = 0.3f;
    h->position[0] = 0.75f;
}