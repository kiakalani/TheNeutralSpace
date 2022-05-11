#include "Text.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Display.h"
#include "Texture.h"
void __text_render(component_t *comp, shader_t *shader)
{
    char *text = (char*)comp->other_components;
    uint64_t length = strlen(text);
    float transformation[16];
    memset(transformation, 0, sizeof(float) * 16);
    transformation[0] =  comp->scale[0] / (float)length;
    transformation[5] = transformation[10] = transformation[15] = 1.0f;
    component_t *shape = scene_get_component(display->external_comps, "quad_buffer");
    for (uint64_t i = 0; i < length; ++i)
    {
        shader_use_shader(shader, transformation, transformation);
        

        char char_name[10];
        sprintf(char_name, "%c_tex", text[i]);
        component_t *cur_tex = scene_get_component(display->external_comps, (const char*)char_name);
        if (!cur_tex) continue;
        //printf("TEXTURE IS %u\n", ((texture_components_t*)cur_tex->other_components)->texture_id);

        transformation[12] = comp->position[0] + (i * (comp->scale[0] / (float)length));
        transformation[13] = comp->position[1];
        glUniformMatrix4fv(glGetUniformLocation(shader->program_id, "transformation_mat"), 1, GL_FALSE, transformation);
        cur_tex->render(cur_tex, shader);

        shape->render(shape, shader);

    }
    glBindTexture(GL_TEXTURE_2D, 0);
}
void text_init(component_t *t, const char *name, const char *text)
{
    component_init(t, name);
    t->other_components = (void*)malloc(sizeof(char) * (strlen(text) + 1));
    sprintf((char*)t->other_components, "%s", text);
    t->shader = scene_get_shader(display->external_comps, "text_shader");
    t->render = __text_render;
}

void text_destroy(component_t *comp)
{
    
}