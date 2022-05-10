#ifndef _CAMERA_H_
#define _CAMERA_H_
#include "Component.h"

typedef struct camera_components
{
    float forward[3];
    float side[3];
    float up[3];
    float field_of_view;
    float far_clipping_plane, near_clipping_plane;

    component_t *object_to_follow;
    
}camera_components_t;

void camera_init(component_t*, float, float, float);


void camera_get_view_mat(component_t*, float*);
void camera_get_projection_mat(component_t*, float*, float);
void camera_transform_vector_by_quat(float[4], float[3]);


void camera_move_forward(component_t*, float);
void camera_move_right(component_t*, float);
void camera_move_up(component_t*, float);


void camera_pitch(component_t*, float);
void camera_roll(component_t*, float);
void camera_yaw(component_t*, float);

void camera_follow_object(component_t*, component_t*);
void camera_stop_following_object(component_t*);
// DONE. TO BE TESTED
#endif