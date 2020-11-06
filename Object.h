#ifndef _OBJECT_H_
#define _OBJECT_H_

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#else
#include <GL/glew.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace std;

#include <string>
#include <vector>
#include <stdio.h>

class Object
{
public:
	glm::mat4 model;
	glm::vec3 color;
    glm::vec3 lightcolor;
    glm::vec3 viewPos;
    glm::vec3 lightPos;
    glm::vec3 ambientlight;
    glm::vec3 diffuselight;
    glm::vec3 specularlight;
    
public:
	glm::mat4 getModel() { return model; }
	glm::vec3 getColor() { return color; }

	virtual void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader, glm::vec3 lightPos) = 0;
	virtual void update() = 0;
    virtual void rotateL(float angle, glm::vec3 axis) = 0;
};

#endif

