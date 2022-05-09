#include "Component.h"
#include <string.h>
#include <stdlib.h>
#include "LMath.h"
#include "Shader.h"
#include <GL/glew.h>
#include <stdio.h>

void __component_sample_render(component_t *comp, shader_t *sh)
{
    if (comp->shader == NULL)
    {
        printf("No shader detected; aborting the render process\n");
        return;
    }
    float transformation[16];
    component_get_transformation_mat(comp, transformation);
    glUniformMatrix4fv(glGetUniformLocation(comp->shader->program_id, "transformation_mat"), 1, GL_FALSE, transformation);
    for (uint64_t i = 0; i < comp->count_components; ++i)
    {
        if (comp->components[i]->render) comp->components[i]->render(comp->components[i], comp->shader);
    }

}

void component_init(component_t *component)
{
    memset(component, 0, sizeof(component_t));
    component->components = (component_t**)malloc((component->size_components = 1) *sizeof(component_t*));
    component->orientation[0] = 1.0f;
    component->scale[0] = 1.0f;
    component->scale[1] = 1.0f;
    component->scale[2] = 1.0f;

    component->render = __component_sample_render;


}


void component_destroy(component_t *comp)
{
    if (comp->other_components) free(comp->other_components);
    free(comp->components);
}





void component_destroy_components(component_t *comp)
{
    for (uint64_t i = 0; i < comp->count_components; ++i)
        component_destroy(comp->components[i]);
    comp->components = (component_t**) realloc(comp->components, sizeof(component_t*) * (comp->size_components = 1));
    comp->count_components = 0;
}


void component_add_component(component_t *dest, component_t *a)
{
    if (dest->size_components <= dest->count_components + 1)
    {
        dest->components = (component_t**)realloc(dest->components, sizeof(component_t*) * (dest->size_components *= 2));
    }
    dest->components[dest->count_components++] = a;
}

void component_remove_component_index(component_t *dest, uint64_t i)
{
    if (i >= dest->count_components) return;
    for (uint64_t j = i; j < dest->count_components - 1; j++)
    {
        dest->components[j] = dest->components[j + 1];
    }
    (dest->count_components)--;


    if (dest->size_components > 3 * dest->count_components)
    {
        dest->components = (component_t**) realloc(dest->components, sizeof(component_t*) * (dest->size_components = dest->size_components / 2 + 1));
    }
}

void component_remove_component(component_t *dest, component_t *rem)
{
    for (uint64_t i = 0; i < dest->size_components; ++i)
    {
        if (dest->components[i] == rem)
        {
            component_remove_component_index(dest, i);
            return;
        }
    }
}

void component_get_transformation_mat(component_t *comp, float *mat)
{
    float translation_mat[16];
    lmath_translate_matrix(comp->position, translation_mat);
    float rotation_mat[16];
    lmath_rotate_matrix(comp->orientation, rotation_mat);
    float scale_mat[16];
    lmath_scale_matrix(comp->scale, scale_mat);

    float trmat[16];
    lmath_multiply_matrix(translation_mat, rotation_mat, trmat);
    lmath_multiply_matrix(trmat, scale_mat, mat);

}


