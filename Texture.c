#include "Texture.h"
#include <string.h>
#include <SOIL/SOIL.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <stdio.h>
void __texture_render(component_t *comp, shader_t *shader)
{
    texture_components_t *tcomps = (texture_components_t*)comp->other_components;
    printf("ADDRESS IS %u AND TEXTURE IS %u\n", glGetUniformLocation(shader->program_id, "tex_add"), tcomps->texture_id);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tcomps->texture_id);

}

void texture_init(component_t *tex, const char *path)
{
    memset(tex, 0, sizeof(component_t));
    tex->other_components = malloc(sizeof(texture_components_t));
    texture_components_t *tcomps = (texture_components_t*)tex->other_components;
    tcomps->texture_id = SOIL_load_OGL_texture(path, SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, 0);
    glActiveTexture(GL_TEXTURE0);

    glBindTexture(GL_TEXTURE_2D, tcomps->texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T , GL_REPEAT);
    
    glGenerateMipmap(GL_TEXTURE_2D);

    tex->render = __texture_render;
    tex->destroy_other_comps = texture_destroy;

}


void texture_destroy(component_t *tex)
{
    texture_components_t *tcomps = (texture_components_t*)tex->other_components;
    glDeleteTextures(1, &tcomps->texture_id);
}