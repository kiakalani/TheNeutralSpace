#include "Player.h"
#include "Display.h"
#include "Camera.h"
#include "LMath.h"
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Bullet.h"
void __player_handle(component_t *comp)
{
    if (glfwGetKey(display->window, GLFW_KEY_SPACE) == GLFW_PRESS)
    {
        component_t *bullet = (component_t*)malloc(sizeof(component_t));
        bullet_init(bullet, comp);
        scene_add_component(display->current_scene, bullet);
    }
}
void player_init(component_t *comp)
{
    component_init(comp, "player");
    component_add_component(comp, scene_get_component(display->external_comps, "ship_texture"));
        component_add_component(comp, scene_get_component(display->external_comps, "ship_buffer"));

    lmath_angle_axis_quat(-3.141522f * 0.2f, 1.0f, 0.0f, 0.0f, comp->orientation);
    camera_follow_object(display->current_scene->camera, comp);
    comp->shader = scene_get_shader(display->external_comps, "texture_shader");
    comp->scale[2] = 0.25f;
    comp->handle = __player_handle;
}