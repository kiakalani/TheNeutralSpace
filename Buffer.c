#include "Buffer.h"
#include <GL/glew.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
void __buffer_render(component_t *buff, shader_t *shader)
{
    
    buffer_components_t *bcomps = (buffer_components_t*)buff->other_components;
    glBindBuffer(GL_ARRAY_BUFFER, bcomps->vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bcomps->ebo);

    uint32_t vpos = glGetAttribLocation(shader->program_id, "vertex");
    uint32_t uv_pos = glGetAttribLocation(shader->program_id, "uv");
    glVertexAttribPointer(vpos, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
    glVertexAttribPointer(uv_pos, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);


    
    glDrawElements(GL_TRIANGLES, bcomps->size_indices, GL_UNSIGNED_INT, NULL);
}


void buffer_init(component_t *buff, const char *name, float *verts, uint64_t cverts, uint32_t *faces, uint64_t cfaces)
{
    memset(buff, 0, sizeof(component_t));
    component_init(buff, name);
    buff->other_components = (void*) malloc(sizeof(buffer_components_t));
    buffer_components_t *bcomps = (buffer_components_t*)(buff->other_components);
    glGenBuffers(1, &(bcomps->vbo));
    glGenBuffers(1, &(bcomps->ebo));
    bcomps->size_indices = cfaces;

    glBindBuffer(GL_ARRAY_BUFFER, bcomps->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * cverts, verts, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bcomps->ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) *cfaces, faces, GL_STATIC_DRAW);
    buff->render = __buffer_render;
}


void buffer_destroy(component_t *b)
{
    buffer_components_t *bcomp = (buffer_components_t*)b->other_components;
    glDeleteBuffers(1, &(bcomp->vbo));
    glDeleteBuffers(1, &(bcomp->ebo));
}


void buffer_create_quad(component_t *buff)
{
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f,       0.0f, 1.0f,
        0.5f, 0.5f, 0.0f,        1.0f, 1.0f,
        0.5f, -0.5f, 0.0f,       1.0f, 0.0f
    };

    uint32_t indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    buffer_init(buff, "quad_buffer", vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(uint32_t));
}


void buffer_create_ship(component_t *buff)
{
    float vertices[] = {
        0.0f, 0.5f, 0.0f,        0.5f, 1.0f,
        -0.25f, 0.25f, 0.5f,     0.25f, 0.75f,
        -0.25, 0.25f, -0.5f,     0.25f, 0.75f,
        -0.2f, 0.25f, 0.5f,      0.30f, 0.75f,
        -0.2f, 0.25f, -0.5f,     0.30f, 0.75f,
        0.2f, 0.25f, 0.5f,       0.7f, 0.75f,
        0.2f, 0.25f, -0.5f,      0.7f, 0.75f,
        0.25f, 0.25f, 0.5f,      0.75f, 0.75f,
        0.25f, 0.25f, -0.5f,     0.75f, 0.75f,
        -0.2f, -0.25f, 0.5f,     0.30f, 0.25f,
        -0.2f, -0.25f, -0.5f,    0.3f, 0.25f,
        0.2f, -0.25f, 0.5f,      0.7f, 0.25f,
        0.2f, -0.25f, -0.5f,     0.7f, 0.25f,
        -0.5f, -0.5f, 0.5f,      0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,     0.0f, 0.0f,
        -0.2f, -0.5f, 0.5f,      0.3f, 0.0f,
        -0.2f, -0.5f, -0.5f,     0.3f, 0.0f,
        0.2f, -0.5f, 0.5f,       0.7f, 0.0f,
        0.2f, -0.5f, -0.5f,      0.7f, 0.0f,
        0.5f, -0.5f, 0.5f,       1.0f, 0.0f,
        0.5f, -0.5f, -0.5f,      1.0f, 0.0f
    };
    uint32_t indices[] = {
        0, 1, 2,
        0, 1, 3,
        0, 2, 4,
        0, 3, 5,
        0, 4, 6,
        0, 5, 7,
        0, 7, 8,
        0, 6, 8,
        3, 9, 11,
        3, 9, 10,
        3, 4, 10,
        4, 10, 12,
        3, 5, 11, 
        4, 6, 12,
        5, 6, 11,
        6, 11, 12,
        9, 13, 15,
        10, 14, 16,
        13, 14, 9,
        10, 9, 14,
        9, 15, 11,
        10, 16, 12,
        15, 17, 11,
        16, 18, 12,
        17, 11, 19,
        18, 12, 20,
        11, 12, 19,
        19, 20, 12
    };
    buffer_init(buff, "ship_buffer", vertices, sizeof(vertices) / sizeof(float), indices, sizeof(indices) / sizeof(uint32_t));
}