//
//  skyBox.cpp
//  CSE167-project1
//
//  Created by siyu meng on 11/11/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#include "skyBox.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

skyBox::skyBox(std::string objFilenameF, std::string objFilenameB, std::string objFilenameR, std::string objFilenameL, std::string objFilenameBT, std::string objFilenameTP)
{
    std::vector<glm::vec3> vertices
    {
        glm::vec3(-500, 500, 500),
        glm::vec3(-500, -500, 500),
        glm::vec3(500, -500, 500),
        glm::vec3(500, 500, 500),
        glm::vec3(-500, 500, -500),
        glm::vec3(-500, -500, -500),
        glm::vec3(500, -500, -500),
        glm::vec3(500, 500, -500)
    };
    
    std::vector<glm::ivec3> indices
    {
        
        // Front face.
        glm::ivec3(0, 1, 2),
        glm::ivec3(2, 3, 0),
        // Back face.
        glm::ivec3(7, 6, 5),
        glm::ivec3(5, 4, 7),
        // Right face.
        glm::ivec3(3, 2, 6),
        glm::ivec3(6, 7, 3),
        // Left face.
        glm::ivec3(4, 5, 1),
        glm::ivec3(1, 0, 4),
        // Top face.
        glm::ivec3(4, 0, 3),
        glm::ivec3(3, 7, 4),
        // Bottom face.
        glm::ivec3(1, 5, 6),
        glm::ivec3(6, 2, 1),
    };
    
    std::vector<std::string> faces
    {
        objFilenameF,
        objFilenameB,
        objFilenameR,
        objFilenameL,
        objFilenameTP,
        objFilenameBT,
    };
    cubemapTexture = loadCubemap(faces);
    
    glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    
    glGenBuffers(1, &skyboxEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, skyboxEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * indices.size(), indices.data(), GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

skyBox::~skyBox()
{
    glDeleteBuffers(1, &skyboxVBO);
    glDeleteBuffers(1, &skyboxEBO);
    glDeleteVertexArrays(1, &skyboxVAO);
}

void skyBox::draw(const glm::mat4 &view, const glm::mat4 &projection, GLuint shader)
{
    glDepthFunc(GL_LEQUAL);
    glUseProgram(shader);
    
    //glm::mat4 n_view = glm::mat4(glm::mat3(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    glUniform1i(glGetUniformLocation(shader, "skybox"), 0);
    
    glBindVertexArray(skyboxVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapTexture);
    
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glDepthFunc(GL_LESS);
    

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    
    glUseProgram(0);
}

void skyBox::update()
{

}

void skyBox::spin(float deg)
{
    
}

unsigned int skyBox::loadCubemap(vector<std::string> faces)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

    int width, height, nrChannels;
    for (unsigned int i = 0; i < faces.size(); i++)
    {
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                         0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data
            );
            stbi_image_free(data);
        }
        else
        {
            std::cout << "Cubemap tex failed to load at path: " << faces[i] << std::endl;
            stbi_image_free(data);
        }
    }
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    return textureID;
}


