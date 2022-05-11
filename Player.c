#include "Player.h"
#include "Display.h"
#include "Camera.h"
#include "LMath.h"
#include <stdio.h>
void player_init(component_t *comp)
{
    component_init(comp, "player");
    component_add_component(comp, scene_get_component(display->external_comps, "ship_texture"));
        component_add_component(comp, scene_get_component(display->external_comps, "ship_buffer"));

    lmath_angle_axis_quat(-3.141522f * 0.2f, 1.0f, 0.0f, 0.0f, comp->orientation);
    camera_follow_object(display->current_scene->camera, comp);
    comp->shader = scene_get_shader(display->external_comps, "texture_shader");
    comp->scale[2] = 0.25f;
}