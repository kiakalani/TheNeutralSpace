#include "Scene.h"
#include <string.h>
#include <stdlib.h>
#include "Camera.h"
#include <stdio.h>
#include "Display.h"
void scene_init(scene_t *s)
{
    memset(s, 0, sizeof(scene_t));
    s->components = (component_t**) malloc(sizeof(component_t*) * (s->components_size = 1));
    s->camera = (component_t*) malloc(sizeof(component_t));
    printf("%X\n", s->camera);
    camera_init(s->camera, 45.0f, 1000.0f, 0.01f);
    s->shaders = (shader_t**) malloc(sizeof(shader_t*) * (s->shaders_size = 1));

}


void scene_destroy(scene_t *s)
{
    for (uint64_t i = 0; i < s->count_components; ++i)
    {
        if (s->components[i]->destroy_other_comps)
            s->components[i]->destroy_other_comps(s->components[i]);
        component_destroy(s->components[i]);
        free(s->components[i]);
    }
    for (uint64_t i = 0; i < s->count_shaders; ++i)
    {
        shader_destroy_shader(s->shaders[i]);
        free(s->shaders[i]);
    }
    free(s->components);
    free(s->shaders);

    component_destroy(s->camera);
    free(s->camera);
}


void scene_add_component(scene_t *s, component_t *c)
{
    if (s->components_size <= s->count_components + 1)
    {
        s->components = (component_t**)realloc(s->components, sizeof(component_t*) * (s->components_size *= 2));
    }
    s->components[s->count_components++] = c;
}

void scene_remove_component(scene_t *s, component_t *c)
{
    for (uint64_t i = 0; i < s->components_size; ++i)
    {
        if (s->components[i] == c)
        {
            scene_remove_component_index(s, i);
            return;
        }
    }
}

void scene_remove_component_index(scene_t *s, uint64_t i)
{
    if (i >= s->count_components) return;
    for (uint64_t j = i; j < s->count_components - 1; j++)
    {
        s->components[j] = s->components[j + 1];
    }
    (s->count_components)--;


    if (s->components_size > 3 * s->count_components)
    {
        s->components = (component_t**) realloc(s->components, sizeof(component_t*) * (s->components_size = s->components_size / 2 + 1));
    }
}

void scene_iterate_components(scene_t *s)
{
    float view_mat[16];
    float proj_mat[16];
    camera_get_view_mat(s->camera, view_mat);
    camera_get_projection_mat(s->camera, proj_mat, ((float)display->width) / ((float)display->height));

    for (intmax_t i = s->count_components - 1; i > -1; --i)
    {
        component_t *cur = s->components[i];
        if (cur->render) 
        {
            shader_use_shader(cur->shader, view_mat, proj_mat);
            cur->render(cur, cur->shader);
        }

        if (cur->handle)
        {
            cur->handle(cur);
        }

        if (cur->update)
        {
            cur->update(cur);
        }
    }

    s->camera->update(s->camera);
    s->camera->handle(s->camera);
}


component_t *scene_get_component(scene_t *scene, const char *item_name)
{
    for (uint64_t i = 0; i < scene->count_components; ++i)
    {
        if (!strcmp(item_name, scene->components[i]->name)) return scene->components[i];
    }
    return NULL;
}

void scene_add_shader(scene_t *scene, shader_t *shader)
{
    if (scene->count_shaders + 1 >= scene->shaders_size) 
    scene->shaders = (shader_t**)realloc(scene->shaders, sizeof(shader_t*) * (scene->shaders_size *= 2));
    scene->shaders[(scene->count_shaders)++] = shader;
}


shader_t *scene_get_shader(scene_t *scene, const char *name)
{
    for (uint64_t i = 0; i < scene->count_shaders; ++i)
    {
        if (!strcmp(scene->shaders[i]->name, name)) return scene->shaders[i];
    }
    return NULL;
}