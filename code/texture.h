#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <iostream>
#include <string>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "shader.h"

class Texture
{
public:
    Texture(const char* texture_path);
    ~Texture();

    void Bind();
private:
    unsigned int texture_id;
};

#endif //TEXTURE_H_