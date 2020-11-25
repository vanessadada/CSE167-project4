//
//  Geometry.hpp
//  CSE167-project1
//
//  Created by siyu meng on 11/14/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#ifndef Geometry_hpp
#define Geometry_hpp

#include <stdio.h>
#include "Node.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

class Geometry : public Node
{
public:
    Geometry(std::string filename, glm::vec3 color, glm::vec3 positionP, glm::vec3 sizeP, int isCylinderP, float degP);
    ~Geometry();
    
    GLuint VAO, VBO, nVBO, EBO;
    
    glm::vec3 position;
    glm::vec3 size;
    float deg;
    
    glm::mat4 modelG;
    glm::mat4 modelMatrix;
    glm::vec3 modelColor;
    glm::vec3 modelPosition;
    int isCylinder;
    glm::vec3 ambient = glm::vec3(0.2,0.2,0.2);
    glm::vec3 diffuse = glm::vec3(10,10,10);
    glm::vec3 specular = glm::vec3(0,0,0);
    float shininess = 0.25;
    std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> faces;
    GLuint shaderProgram;
    glm::mat4 modelProjection;
    glm::mat4 viewMatirx;
    glm::vec3 cameraPos = glm::vec3(0,0,20);
    glm::vec3 lightPos = glm::vec3(4,-4,-4);
    glm::vec3 lightColor = glm::vec3(1,1,1);
    
    void setMatrix(glm::mat4 modelView);
    
    void setView(glm::mat4 view) {viewMatirx = view;};
    void setShader(GLuint shader) {shaderProgram = shader;};
    void setProjection(glm::mat4 projection) {modelProjection = projection;};
    
    void init(std::string filename);
    void renderModel(glm::mat4& view, glm::mat4& projection, GLuint shader);
    void draw(const glm::mat4 &matrixC);
    void update(const int isRotate, const int isCenter, const int isUpdown);
    void spin(const float deg);
    void around(float deg);
    void updown(glm::vec3 move);
    int isUp, counter;
};

#endif /* Geometry_hpp */
