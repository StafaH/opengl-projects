#include "camera.h"
#include "glm/gtc/matrix_transform.hpp"

Camera::Camera(glm::vec3 camera_position, glm::vec3 camera_target)
{
    position = camera_position;

    world_up = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = -90.0f;
    pitch = 0.0f;

    movement_speed = 2.5f;
    mouse_sensetivity = 0.1f;
    zoom = 45.0f;

    UpdateCameraVectors();
}

Camera::~Camera()
{
}

void Camera::UpdatePosition(glm::vec3 direction, float delta_time)
{
    float velocity = movement_speed * delta_time;
    position += (direction * velocity);
}

void Camera::UpdateView(float x_offset, float y_offset)
{
    x_offset *= mouse_sensetivity;
    y_offset *= mouse_sensetivity;

    yaw += x_offset;
    pitch += y_offset;

    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    UpdateCameraVectors();
}

void Camera::UpdateZoom(float yoffset)
{
    if (zoom >= 1.0f && zoom <= 45.0f)
            zoom -= yoffset;
        if (zoom <= 1.0f)
            zoom = 1.0f;
        if (zoom >= 45.0f)
            zoom = 45.0f;
}

glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(position, position + forward, up);
}

void Camera::UpdateCameraVectors()
{
    // Calculate the new front vector
    glm::vec3 camera_front;
    camera_front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    camera_front.y = sin(glm::radians(pitch));
    camera_front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward = glm::normalize(camera_front);

    // Calculate the new right vector
    right = glm::normalize(glm::cross(forward, world_up));
    up = glm::normalize(glm::cross(right, forward));
}