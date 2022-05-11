#include "Camera.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "LMath.h"
#include <math.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Display.h"
void camera_transform_vector_by_quat(float quat[4], float vert[3])
{
    float vec[3];
    memcpy(vec, &(quat[1]), sizeof(float) * 3);

    float a = quat[0];


    float final_result[3];

    float vec_1[3];
    memcpy(vec_1, vec, sizeof(float) * 3);
    lmath_multiply_vector_float(vec_1, 2.0f * lmath_dot_product(vert, vec));

    float vec_2[3];
    memcpy(vec_2, vert, sizeof(float) * 3);
    lmath_multiply_vector_float(vec_2, a * a - lmath_dot_product(vec, vec));


    float vec_3[3];

    lmath_cross_product(vec, vert, vec_3);
    lmath_multiply_vector_float(vec_3, 2.0f * a);

    lmath_add_vectors(vec_1, vec_2);
    lmath_add_vectors(vec_1, vec_3);

    memcpy(vert, vec_1, sizeof(float) * 3);
}

void camera_move_forward(component_t *cam, float spd)
{
    camera_components_t *cam_comps = (camera_components_t*)cam->other_components;
    float movement[3];
    memcpy(movement, cam_comps->forward, sizeof(float) * 3);
    lmath_multiply_vector_float(movement, spd);
    lmath_add_vectors(cam->position, movement);
}

void camera_move_right(component_t *cam, float spd)
{
    camera_components_t *cam_comps = (camera_components_t*)cam->other_components;
    float movement[3];
    memcpy(movement, cam_comps->side, sizeof(float) * 3);
    lmath_multiply_vector_float(movement, spd);
    lmath_add_vectors(cam->position, movement);
}

void camera_move_up(component_t *cam, float spd)
{
    camera_components_t *cam_comps = (camera_components_t*)cam->other_components;
    float movement[3];
    memcpy(movement, cam_comps->up, sizeof(float) * 3);
    lmath_multiply_vector_float(movement, spd);
    lmath_add_vectors(cam->position, movement);
}


void camera_pitch(component_t *cam, float angle)
{
    float angles[4];
    lmath_angle_axis_quat(angle, 0.0f, 1.0f, 0.0f, angles);
    float result[4];
    lmath_quat_multiply(angles, cam->orientation, result);
    lmath_normalize(result, 4);
    memcpy(cam->orientation, result, sizeof(float) * 4);
}
void camera_roll(component_t *cam, float angle)
{
    float angles[4];
    lmath_angle_axis_quat(angle, 0.0f, 0.0f, 1.0f, angles);
    float result[4];
    lmath_quat_multiply(angles, cam->orientation, result);
    lmath_normalize(result, 4);
    memcpy(cam->orientation, result, sizeof(float) * 4);
}
void camera_yaw(component_t *cam, float angle)
{
    float angles[4];
    lmath_angle_axis_quat(angle, 1.0f, 0.0f, 0.0f, angles);
    float result[4];
    lmath_quat_multiply(angles, cam->orientation, result);
    lmath_normalize(result, 4);
    memcpy(cam->orientation, result, sizeof(float) * 4);
}

void __camera_update(component_t *cam)
{
    camera_components_t *cam_comps = (camera_components_t*)cam->other_components;
    float fwd[3];
    memset(fwd, 0, sizeof(float) * 3);
    fwd[2] = 1.0f;


    float up[3];
    memset(up, 0, sizeof(float) * 3);
    up[1] = 1.0f;
    

    camera_transform_vector_by_quat(cam->orientation, fwd);
    camera_transform_vector_by_quat(cam->orientation, up);

    

    lmath_normalize(fwd, 3);
    lmath_normalize(up, 3);
    
    lmath_cross_product(up, fwd, cam_comps->side);
    lmath_normalize(cam_comps->side, 3);

    memcpy(cam_comps->forward, fwd, sizeof(float) * 3);
    memcpy(cam_comps->up, up, sizeof(float) * 3);
    
    
    if (cam_comps->object_to_follow)
    {
        float fwd_cpy[3];
        memcpy(fwd_cpy, fwd, sizeof(float) * 3);
        lmath_multiply_vector_float(fwd_cpy, -1.0f);
        
        component_t *comp = cam_comps->object_to_follow;
        lmath_multiply_vector_float(fwd_cpy, 4.0f);

        float up_cpy[3];
        memcpy(up_cpy, up, sizeof(float) * 3);
        lmath_multiply_vector_float(up_cpy, -1.0f);


        memcpy(comp->position, cam->position, sizeof(float) * 3);
        //lmath_print_vector(comp->position, 3);
        
        lmath_add_vectors(comp->position, fwd_cpy);   
        lmath_add_vectors(comp->position, up_cpy);

        //memcpy(comp->orientation, cam->orientation, sizeof(float) * 4);
            
    }

}

void __camera_handle(component_t *cam)
{
    if (glfwGetKey(display->window, GLFW_KEY_S) == GLFW_PRESS)
    {
        camera_move_forward(cam, display->delta_time);
    }
    if (glfwGetKey(display->window, GLFW_KEY_W) == GLFW_PRESS)
    {
        camera_move_forward(cam, -1.0f * display->delta_time);
    }
    if (glfwGetKey(display->window, GLFW_KEY_A) == GLFW_PRESS)
    {
        camera_move_right(cam, -1.0f * display->delta_time);
    }
    if (glfwGetKey(display->window, GLFW_KEY_D) == GLFW_PRESS)
        camera_move_right(cam,  display->delta_time);

    if (glfwGetKey(display->window, GLFW_KEY_Q) == GLFW_PRESS)
        camera_move_up(cam, display->delta_time);
    if (glfwGetKey(display->window, GLFW_KEY_E) == GLFW_PRESS)
        camera_move_up(cam, -1.0f * display->delta_time);

    if (glfwGetKey(display->window, GLFW_KEY_J) == GLFW_PRESS)
    {
                if (lmath_get_rotation_axis(cam->orientation, 1) > 3.141522f * -0.1f)

        camera_pitch(cam, -1.0f * (3.141522 * display->delta_time * 0.1f));
    }
    if (glfwGetKey(display->window, GLFW_KEY_L) == GLFW_PRESS)
    {
                if (lmath_get_rotation_axis(cam->orientation, 1) < 3.141522f * 0.1f)

        camera_pitch(cam, (3.141522 * display->delta_time * 0.1f));
    }

    if (glfwGetKey(display->window, GLFW_KEY_K) == GLFW_PRESS)
    {
        camera_yaw(cam, -1.0f * (3.141522 * display->delta_time * 0.1f));
    }


    if (glfwGetKey(display->window, GLFW_KEY_I) == GLFW_PRESS)
    {
        camera_yaw(cam, (3.141522 * display->delta_time * 0.1f));
    }

    if (glfwGetKey(display->window, GLFW_KEY_U) == GLFW_PRESS)
    {
        camera_roll(cam, -1.0f * (3.141522 * display->delta_time * 0.1f));
    }

    
    if (glfwGetKey(display->window, GLFW_KEY_O) == GLFW_PRESS)
    {
        camera_roll(cam, (3.141522 * display->delta_time * 0.1f));
    }

    printf("ROTATIONX: %f ROTATIONY: %f ROTATIONZ: %f\n", lmath_get_rotation_axis(cam->orientation, 0),
    lmath_get_rotation_axis(cam->orientation, 1), lmath_get_rotation_axis(cam->orientation, 2));
}

void camera_init(component_t *cam, float fov, float fcp, float ncp)
{
    memset(cam, 0, sizeof(component_t));
    component_init(cam);
    camera_components_t *cam_comps = (camera_components_t*)malloc(sizeof(camera_components_t));
    memset(cam_comps, 0, sizeof(camera_components_t));
    cam_comps->far_clipping_plane = fcp;
    cam_comps->near_clipping_plane = ncp;
    cam_comps->field_of_view = fov;

    cam_comps->forward[2] = 1.0f;
    cam_comps->side[0] = 1.0f;
    cam_comps->up[2] = 1.0f;
    cam->other_components = (void*)cam_comps;
    cam->update = __camera_update;
    cam->handle = __camera_handle;
}

void camera_get_view_mat(component_t *cam, float *mat)
{
    memset(mat, 0, sizeof(float) * 16);
    camera_components_t *cam_comps = (camera_components_t*)cam->other_components;
    mat[0] = cam_comps->side[0];
    mat[4] = cam_comps->side[1];
    mat[8] = cam_comps->side[2];

    mat[1] = cam_comps->up[0];
    mat[5] = cam_comps->up[1];
    mat[9] = cam_comps->up[2];

    mat[2] = cam_comps->forward[0];
    mat[6] = cam_comps->forward[1];
    mat[10] = cam_comps->forward[2];

    float position[3];
    memcpy(position, cam->position, sizeof(float) * 3);


    mat[12] = lmath_dot_product(cam_comps->side, position) * -1.0f;
    mat[13] = lmath_dot_product(cam_comps->up, position) * -1.0f;
    mat[14] = lmath_dot_product(cam_comps->forward, position) * -1.0f;

    mat[15] = 1.0f;

    
    
    

}

void camera_get_projection_mat(component_t *cam, float *mat, float ratio)
{
    camera_components_t *cam_comps = (camera_components_t*)cam->other_components;
    float th = tan(((3.141522f / 180) * cam_comps->field_of_view) * 0.5f);
    memset(mat, 0, sizeof(float) * 16);
    mat[0] = mat[5] = mat[10] = mat[15] = 1.0f;
 
    mat[0] = 1.0f / (ratio * th);
    mat[5] = 1.0f / th;
    mat[10] = -(cam_comps->far_clipping_plane + cam_comps->near_clipping_plane) / (cam_comps->far_clipping_plane - cam_comps->near_clipping_plane);
    mat[11] = -1.0f;
    mat[14] = (2.0f * cam_comps->far_clipping_plane * cam_comps->near_clipping_plane) / (cam_comps->far_clipping_plane - cam_comps->near_clipping_plane);

}


void camera_follow_object(component_t *cam, component_t *obj)
{
    camera_components_t *comp = (camera_components_t*) cam->other_components;
    comp->object_to_follow = obj;
}
void camera_stop_following_object(component_t *cam)
{
    camera_components_t *comp = (camera_components_t*) cam->other_components;
    comp->object_to_follow = NULL;
}