#include "Shader.h"
#include "Component.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void shader_use_shader(shader_t *s, float *camera_view, float *camera_projection)
{
    glUseProgram(s->program_id);
    glUniformMatrix4fv(glGetUniformLocation(s->program_id, "view_mat"), 1, GL_FALSE, camera_view);
    glUniformMatrix4fv(glGetUniformLocation(s->program_id, "projection_mat"), 1, GL_FALSE, camera_projection);
    glUniform1f(glGetUniformLocation(s->program_id, "time"), (float)glfwGetTime());
}


char *shader_read_file(const char *path)
{
    uint64_t count_comps, size_comps;
    char *comps = (char*)malloc(sizeof(char) * (size_comps = 2));
    *comps = count_comps = 0;
    FILE *file = fopen(path, "r");
    if (!file)
    {
        printf("File %s Not Found\n", path);
        free(comps);
        return NULL;
    }
    char current;
    while ((current = (char)fgetc(file)) != EOF)
    {
        if (count_comps + 2 >= size_comps)
        {
            comps = (char*)realloc(comps, sizeof(char) * (size_comps *= 2));
        }
        comps[count_comps++] = current;
        comps[count_comps] = 0;
    }
    fclose(file);
    return (char*)realloc(comps, sizeof(char) * (count_comps + 1));
    
}

uint32_t __shader_create_shader(GLenum shader_type, const char *path)
{
    char *shader_code = shader_read_file(path);
    if (!shader_code)
    {
        return -1;
    }
    
    char *compile_message = (char*) malloc(sizeof(char) * 1000);
    int success;
    uint32_t shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, (const char**)(&shader_code), NULL);
    glCompileShader(shader);

    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(shader, 1000, NULL, compile_message);
        printf("Error compiling shader %s\n%s\n", path, compile_message);
        glDeleteShader(shader);
        shader = -1;
    }
    free(compile_message);
    free(shader_code);

    return shader;
}


void shader_init_shader(shader_t *shader, const char *vertex_shader_path, const char *fragment_shader_path)
{
    uint32_t vertex_shader = __shader_create_shader(GL_VERTEX_SHADER, vertex_shader_path);
    if (vertex_shader == -1) return;
    uint32_t fragment_shader = __shader_create_shader(GL_FRAGMENT_SHADER, fragment_shader_path);
    if (fragment_shader == -1)
    {
        glDeleteShader(vertex_shader);
        return;
    }
    memset(shader, 0, sizeof(shader_t));
    shader->program_id = glCreateProgram();
    glAttachShader(shader->program_id, vertex_shader);
    glAttachShader(shader->program_id, fragment_shader);
    glLinkProgram(shader->program_id);

    int success;
    char *message = (char*)malloc(sizeof(char) * 1000);
    glGetProgramiv(shader->program_id, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(shader->program_id, 1000, NULL, message);
        printf("Error linking program:\n%s\n", message);
    }
    free(message);
    glDeleteShader(vertex_shader);
    glDeleteShader(fragment_shader);
    
}


void shader_destroy_shader(shader_t *shader)
{
    glDeleteProgram(shader->program_id);
}