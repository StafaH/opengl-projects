#ifndef CAMERA_H_
#define CAMERA_H_

#include <glm/glm.hpp>

class Camera {
public:
    Camera(glm::vec3 camera_position, glm::vec3 camera_target);
    ~Camera();

    void UpdatePosition(glm::vec3 direction, float delta_time);
    void UpdateView(float x_offset, float y_offset);
    void UpdateZoom(float yoffset);

    glm::mat4 GetViewMatrix();
    
    glm::vec3 position;
    glm::vec3 forward;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    float yaw;
    float pitch;

    float movement_speed;
    float mouse_sensetivity;
    float zoom;
private:

    void UpdateCameraVectors();
};

#endif // CAMERA_H_