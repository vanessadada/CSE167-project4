//
//  ParticleSystem.hpp
//  CSE167-project1
//
//  Created by siyu meng on 12/6/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#ifndef ParticleSystem_hpp
#define ParticleSystem_hpp

#include <stdio.h>
#include "Object.h"
#include "BoundingSphere.hpp"
#include <vector>
#include <iostream>

class ParticleSystem{
private:
    struct Particle{
        glm::vec3 position;
        glm::vec3 velocity;
        glm::vec3 color;
        glm::vec4 testColor;
        float life;
        Particle() : position(glm::vec3(0)), velocity(glm::vec3(0.01,0,0)), color(glm::vec3(1,1,0)), life(0.0f) { }
    };
    
    static const int MAX_PARTICLES = 200;
    static const int PARTICLE_LIFE = 3;
    static const int pointSize = 3;
    
    
    GLuint VAO;
    GLuint VBO;
    
    std::vector<Particle> particles;
    std::vector<glm::vec3> position_data;
    
public:
    ParticleSystem(BoundingSphere * astro);
    ~ParticleSystem();
    
    void update(float deltaTime, BoundingSphere* astro, unsigned int newParticles);
    void draw(GLuint shader, const glm::mat4& view, const glm::mat4& projection, glm::vec3 posit);
    void updateDis(float deltaTime, BoundingSphere* astro, unsigned int newParticles);
    
    void spawnParticles(BoundingSphere* astro, Particle * particle);
    
    unsigned int firstUnusedParticle();
    
    glm::mat4 model;
    
    float intensity = 0;
    int isDone = 0;
    
    int isDisDone = 0;
    int isBegin = 0;
};
#endif /* ParticleSystem_hpp */
