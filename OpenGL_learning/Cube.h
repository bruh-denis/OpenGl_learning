#ifndef CUBE_CLASS_H
#define CUBE_CLASS_H

#include <glm/glm.hpp>
#include"shaderClass.h"

class Cube {
public:
    Cube();
    ~Cube();

    void loadTexture(const char* texturePath);
    void setPosition(const glm::vec3& position);
    glm::vec3 getPosition() const;
    void draw(GLuint shaderProgram); // Shader program to use for drawing

private:
    GLuint VAO, VBO, EBO; // Vertex Array Object, Vertex Buffer Object, Element Buffer Object
    GLuint texture;
    glm::vec3 position;

    void setupCube();
};

#endif

