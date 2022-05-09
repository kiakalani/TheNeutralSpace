#ifndef _LMATH_H_
#define _LMATH_H_
#include <stdint.h>

void lmath_translate_matrix(float[3], float[16]);
void lmath_rotate_matrix(float[4], float[16]);
void lmath_scale_matrix(float[3], float[16]);

void lmath_multiply_matrix(float[16], float[16], float[16]);

void lmath_add_vectors(float[3], float[3]);
void lmath_multiply_vectors(float[3], float[3]);
float lmath_dot_product(float[3], float[3]);
void lmath_cross_product(float[3], float[3], float[3]);

void lmath_multiply_vector_float(float[3], float);

void lmath_angle_axis_quat(float, float, float, float, float[4]);

void lmath_quat_multiply(float[4], float[4], float[4]);

void lmath_normalize(float*, uint8_t);
float lmath_length(float*, uint8_t);
void lmath_print_mat4(float *mat);
void lmath_print_vector(float *vec, uint8_t);
float lmath_distance(float*, float*, uint8_t);
float lmath_length_pow2(float*, uint8_t);
#endif