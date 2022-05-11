#include "Component.h"
#include <string.h>
#include <stdlib.h>
#include "LMath.h"
#include "Shader.h"
#include <GL/glew.h>
#include <stdio.h>
#include <math.h>
#include "Display.h"
#include "Camera.h"

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
    //component_face_component(comp, display->current_scene->camera);

}

void component_init(component_t *component, const char *name)
{
    memset(component, 0, sizeof(component_t));
    component->components = (component_t**)malloc((component->size_components = 1) *sizeof(component_t*));
    component->orientation[0] = 1.0f;
    component->scale[0] = 1.0f;
    component->scale[1] = 1.0f;
    component->scale[2] = 1.0f;
    component->name = (char*)malloc(sizeof(char) * (strlen(name) + 2));
    sprintf(component->name, "%s", name);

    component->render = __component_sample_render;


}


void component_destroy(component_t *comp)
{
    if (comp->other_components) free(comp->other_components);
    free(comp->components);
    free(comp->name);
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


void component_face_component(component_t *first, component_t *second)
{


    float forward[3];
    memcpy(forward, first->position, sizeof(float) * 3);
    lmath_multiply_vector_float(forward, -1.0f);
    lmath_add_vectors(forward, second->position);
    lmath_normalize(forward, 3);

    float rot_axis[3];
    float fwd_vec[3];
    memset(fwd_vec, 0, sizeof(float) * 3);
    fwd_vec[2] = 1.0f;
    lmath_cross_product(fwd_vec, forward, rot_axis);

    float dot = lmath_dot_product(fwd_vec, forward);
    first->orientation[0] = dot + 1.0f;
    memcpy(&(first->orientation[1]), rot_axis, sizeof(float) * 3);

    lmath_normalize(first->orientation, 4);



}

void component_forward_vec(component_t *comp, float fwd[3])
{
    float vec[3];
    memset(vec, 0, sizeof(float) * 3);
    vec[2] = 1.0f;
    camera_transform_vector_by_quat(comp->orientation, vec);
    lmath_normalize(vec, 3);

    memcpy(fwd, vec, sizeof(float) * 3);
}

void component_side_vec(component_t *comp, float side[3])
{
    float vec[3];
    memset(vec, 0, sizeof(float) * 3);
    vec[0] = 1.0f;
    camera_transform_vector_by_quat(comp->orientation, vec);
    lmath_normalize(vec, 3);

    memcpy(side, vec, sizeof(float) * 3);
}

void component_up_vec(component_t *comp, float up[3])
{
    float vec[3];
    memset(vec, 0, sizeof(float) * 3);
    vec[1] = 1.0f;
    camera_transform_vector_by_quat(comp->orientation, vec);
    lmath_normalize(vec, 3);

    memcpy(up, vec, sizeof(float) * 3);
}