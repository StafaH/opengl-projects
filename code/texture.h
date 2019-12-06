#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Texture {
public:
    Texture(const char* texture_path);
    ~Texture();

    void Bind();

    glm::vec3 camera_position;
    glm::vec3 camera_up;
    glm::vec3 camera_right;
    glm::vec3 camera_front;

private:
    unsigned int texture_id;
};

#endif //TEXTURE_H_