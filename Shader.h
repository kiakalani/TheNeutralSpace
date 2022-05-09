#ifndef _SHADER_H_
#define _SHADER_H_
#include <stdint.h>
typedef struct shader
{
    uint32_t program_id;
}shader_t;


void shader_use_shader(shader_t*, float*, float*);
void shader_init_shader(shader_t*, const char*, const char*);
void shader_destroy_shader(shader_t*);


char *shader_read_file(const char*);
// DONE TO BE TESTED
#endif