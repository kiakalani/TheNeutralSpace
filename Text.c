#include "Text.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Display.h"
#include "Texture.h"
void __text_render(component_t *comp, shader_t *shader)
{
    char *text = ((text_components_t*)(comp->other_components))->text;
    uint64_t length = strlen(text);
    float transformation[16];
    memset(transformation, 0, sizeof(float) * 16);
    transformation[0] =  comp->scale[0] / (float)length;
    transformation[5] = comp->scale[1];
    transformation[10] = 
    transformation[15] = 1.0f;
    component_t *shape = scene_get_component(display->external_comps, "quad_buffer");
    for (uint64_t i = 0; i < length; ++i)
    {
        shader_use_shader(shader, transformation, transformation);
        

        char char_name[10];
        sprintf(char_name, "%c_tex", text[i]);
        component_t *cur_tex = scene_get_component(display->external_comps, (const char*)char_name);
        if (!cur_tex) continue;

        transformation[12] = comp->position[0] + (i * (comp->scale[0] / (float)length)) - comp->scale[0] * 0.5f;
        transformation[13] = comp->position[1];
        glUniformMatrix4fv(glGetUniformLocation(shader->program_id, "transformation_mat"), 1, GL_FALSE, transformation);
        float *color = ((text_components_t*)(comp->other_components))->color;
        glUniform3fv(glGetUniformLocation(shader->program_id, "color"), 1, color);
        cur_tex->render(cur_tex, shader);

        shape->render(shape, shader);

    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
void text_init(component_t *t, const char *name, const char *text, float color[3])
{
    component_init(t, name);
    t->other_components = (void*)calloc(sizeof(text_components_t), 1);
    ((text_components_t*)(t->other_components))->text = (char*)malloc(sizeof(char) * (strlen(text) + 1));
    sprintf(((text_components_t*)(t->other_components))->text, "%s", text);
    t->shader = scene_get_shader(display->external_comps, "text_shader");
    t->render = __text_render;
    memcpy(((text_components_t*)(t->other_components))->color, color, sizeof(float) * 3);
    t->destroy_other_comps = text_destroy;
}

void text_destroy(component_t *comp)
{
    free(((text_components_t*)(comp->other_components))->text);
}