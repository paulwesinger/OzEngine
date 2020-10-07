/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

// ---------------------------------------------
// tools für calculatiopn with vectors 
// ---------------------------------------------

//#include <glm/detail/func_trigonometric.inl>
#include <glm/trigonometric.hpp>
#include "vecmath.h"



void rotX( glm::vec3 &vec, float angle ) {
    
    float radian = glm::radians( angle);
    
    vec.y = vec.y * cos(radian) - vec.z * sin(radian);
    vec.z = vec.y * sin(radian) + vec.z * cos(radian);
    
    
    //vec.y = vec.y * cos(radian) - vec.z * sin(radian);
    //vec.z = vec.y * sin(radian) + vec.z * cos(radian);

}

void rotY( glm::vec3 &vec, float angle ) {
    float radian = glm::radians( angle);
    
    vec.x = vec.x * cos(radian) + vec.z * sin(radian);
    vec.z = vec.z * -sin(radian) + vec.z * cos(radian);
}

void rotZ( glm::vec3 & vec, float angle ) {
    float radian = glm::radians(angle) ;
    
    vec.x = vec.x * cos(radian) - vec.y * -sin(radian);
    vec.y = vec.x * sin(radian) + vec.y * cos(radian);
}


void rotX( glm::vec3 &vec, double angle ) {
    
    double radian = glm::radians( angle);
    
    vec.z = vec.z * cos(radian) - vec.y * sin(radian);
    vec.y = vec.z * sin(radian) + vec.y * sin(radian);
    
    //vec.y = vec.y * cos(angle) - vec.z * sin(angle);
    //vec.z = vec.y * sin(angle) + vec.z * cos(angle);

}

void rotY( glm::vec3 &vec, double angle ) {
    float radian = glm::radians( angle);
    
    vec.x = vec.x * cos(radian) - vec.z * sin(radian);
    vec.z = vec.z * -sin(radian)  + vec.z * cos(radian);
}

void rotZ( glm::vec3 & vec, double angle ) {
    float radian = glm::radians(angle) ;
    
    vec.x = vec.x * cos(radian) - vec.y * -sin(radian);
    vec.y = vec.x * sin(radian) + vec.y * cos(radian);
}

//=======================================================
// Calc 2D circle data
//=======================================================

void calccircle(float radius, float angle, glm::vec2 & point) {
    
    float radian = glm::radians( angle);
    
    point.x = radius * cos(radian);
    point.y = radius * sin(radian);
}


void checkdegree(float & angle) {
    if (angle == 0.0f )
        return;
    
    if ( angle > 360.0f) {
        angle -= 360.0f;
        return;
    }
    
    if (angle < -360.0f ) 
        angle += 360; 
}

void checkdegree(double & angle) {
    if (angle == 0.0f )
        return;
    
    if ( angle > 359.0f) {
        angle -= 360.0f;
        return;
    }
    
    if (angle < 0.0f ) 
        angle = 360.0f + angle; 
}
