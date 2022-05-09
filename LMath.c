#include "LMath.h"
#include <string.h>
#include <math.h>
#include <stdio.h>
void lmath_translate_matrix(float position[3], float mat[16])
{
    memset(mat, 0, sizeof(float) * 16);
    mat[0] = mat[5] = mat[10] = mat[15] = 1.0f;
    mat[12] = position[0];
    mat[13] = position[1];
    mat[14] = position[2];
}

void lmath_rotate_matrix(float quat[4], float mat[16])
{
    memset(mat, 0, sizeof(float) * 16);
    mat[0] = mat[5] = mat[10] = mat[15] = 1.0f;

    mat[0] = 1.0 - 2.0 * (quat[2] * quat[2] + quat[3] * quat[3]);
    mat[1] = 2.0 * (quat[1] * quat[2] + quat[0] * quat[3]);
    mat[2] = 2.0 * (quat[1] * quat[3] - quat[2] * quat[0]);

    mat[4] = 2.0 * quat[1] * quat[2] - 2.0 * quat[3] * quat[0];
    mat[5] = 1.0 - 2.0 * (quat[1] * quat[1] + quat[3] * quat[3]);
    mat[6] = 2.0 * quat[2] * quat[3] + 2.0 * quat[1] * quat[0];


    mat[8] = 2.0 * (quat[1] * quat[3] + quat[2] * quat[0]);
    mat[9] = 2.0 * (quat[2] * quat[3] - quat[1] * quat[0]);
    mat[10] = 1.0 - 2.0 * (quat[1] * quat[1] + quat[2] * quat[2]);
    
}

void lmath_scale_matrix(float scale[3], float mat[16])
{
    memset(mat, 0, sizeof(float) * 16);
    mat[0] = scale[0];
    mat[5] = scale[1];
    mat[10] = scale[2];
    mat[15] = 1.0f; 
}

void lmath_multiply_matrix(float f_mat[16], float n_mat[16], float d_mat[16])
{
    memset(d_mat, 0, sizeof(float) * 16);
    for (uint8_t r = 0; r < 4; ++r)
    {
        for (uint8_t c = 0; c < 4; ++c)
        {
            for (uint8_t i = 0; i < 4; ++i)
            {
                d_mat[r * 4 + c] += f_mat[i * 4 + c] * n_mat[r * 4 + i];
            }
        }
    }
}


void lmath_add_vectors(float dest[3], float src[3])
{
    for (uint8_t i = 0; i < 3; ++i) dest[i] += src[i];
}

void lmath_multiply_vectors(float dest[3], float src[3])
{
    for (uint8_t i = 0; i < 3; ++i) dest[i] *= src[i];
}

float lmath_dot_product(float first[3], float second[3])
{
    float sum = 0.0f;
    for (uint8_t i = 0; i < 3; ++i) sum += first[i] * second[i];
    return sum;
}

void lmath_cross_product(float first[3], float second[3], float dest[3])
{
    dest[0] = first[1] * second[2] - first[2] * second[1];
    dest[1] = first[2] * second[0] - first[0] * second[2];
    dest[2] = first[0] * second[1] - first[1] * second[0];
}

void lmath_multiply_vector_float(float vec[3], float f)
{
    for (uint8_t i = 0; i < 3; ++i) vec[i] *= f;
}

void lmath_angle_axis_quat(float a, float x, float y, float z, float quat[4])
{
    quat[0] = cos(((double)a) * 0.5);
    float s_val = sin(((double)a) * 0.5);
    quat[1] = x * s_val;
    quat[2] = y * s_val;
    quat[3] = z * s_val;
}

void lmath_quat_multiply(float f_q[4], float n_q[4], float dest_q[4])
{
    dest_q[0] = f_q[0] * n_q[0] - f_q[1] * n_q[1] - f_q[2] * n_q[2] - f_q[3] * n_q[3];
    dest_q[1] = f_q[0] * n_q[1] + f_q[1] * n_q[0] + f_q[2] * n_q[3] - f_q[3] * n_q[2];
    dest_q[2] = f_q[0] * n_q[2] + f_q[2] * n_q[0] + f_q[3] * n_q[1] - f_q[1] * n_q[3];
    dest_q[3] = f_q[0] * n_q[3] + f_q[3] * n_q[0] + f_q[1] * n_q[2] - f_q[2] * n_q[1];
}

float lmath_length(float *vec, uint8_t d)
{
    float sum_pow_2 = 0.0f;
    for (uint8_t i = 0; i < d; ++i) sum_pow_2 += vec[i] * vec[i];
    return sum_pow_2;
}

void lmath_normalize(float *vec, uint8_t d)
{
    float len = lmath_length(vec, d);
    if (len <= 0.0f) return;

    for (uint8_t i = 0; i < d; ++i)
    {
        vec[i] /= len;
    }
}


void lmath_print_mat4(float *mat)
{
    printf("\\------\\\n");
    for (uint8_t i = 0; i < 4; ++i)
    {
        printf("|\t%f\t%f\t%f\t%f\t|\n", mat[4 * i], mat[4 * i + 1], mat[4 * i + 2], mat[4 * i + 3]);
    }
    printf("\\------\\\n");
}

void lmath_print_vector(float *vec, uint8_t d)
{
    printf("\\-----\\\n|\t");
    for (uint8_t i = 0; i < d; ++i)
    {
        printf("%f\t", vec[i]);
    }
    printf("\n\\-----\\\n");
}

