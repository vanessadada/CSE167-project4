//
//  ParticleSystem.cpp
//  CSE167-project1
//
//  Created by siyu meng on 12/6/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#include "ParticleSystem.hpp"

ParticleSystem::ParticleSystem(BoundingSphere * astro)
{
    model = glm::mat4(1);
    model = glm::translate(glm::mat4(1), astro->center) * model;
    model = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(1,0,0)) * model;
    
    position_data = {
        glm::vec3(-1,1,1),
//        glm::vec3(-1,-1,1),
//        glm::vec3(1,-1,1),
//        glm::vec3(1,1,1)
    };
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*position_data.size(), position_data.data(), GL_STATIC_DRAW);
    // set mesh attributes
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glBindVertexArray(0);
    
    for (unsigned int i = 0; i < MAX_PARTICLES; ++i)
    {
//        Particle particle;
//        spawnParticles(astro, &particle);
//        this->particles.push_back(particle);
            this->particles.push_back(Particle());
    }
}

ParticleSystem::~ParticleSystem()
{
    
}

void ParticleSystem::draw(GLuint shader, const glm::mat4& view, const glm::mat4& projection, glm::vec3 posit)
{
    glUseProgram(shader);
    
//    model = glm::translate(glm::mat4(1), posit) * model;
//    model = glm::rotate(glm::mat4(1), glm::radians(90.f), glm::vec3(1,0,0));
    
    for (auto& tiny: particles){
        if (tiny.life > 0.0f){
            glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
            glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
            glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
            glUniform4fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(tiny.testColor));
            glUniform3fv(glGetUniformLocation(shader, "offset"), 1, glm::value_ptr(tiny.position));
            glUniform3fv(glGetUniformLocation(shader, "endColor"), 1, glm::value_ptr(glm::vec3(1,1,0)));
            glUniform3fv(glGetUniformLocation(shader, "startColor"), 1, glm::value_ptr(tiny.color));
            glUniform1f(glGetUniformLocation(shader, "fixedIntensity"), intensity);
            
            glBindVertexArray(VAO);
            
            glPointSize(pointSize);
            
            glDrawArrays(GL_POINTS, 0, position_data.size());
//            glDrawArrays(GL_TRIANGLES, 0, 6);
            glBindVertexArray(0);
        }
    }
    glUseProgram(0);
}

void ParticleSystem::update(float deltaTime, BoundingSphere* astro, unsigned int newParticles)
{
    for (unsigned int i = 0; i < newParticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle();
        this->spawnParticles(astro, &particles[unusedParticle]);
    }
    
    for (unsigned int i = 0; i < MAX_PARTICLES; ++i){
        Particle &p = particles[i];
        p.life -= deltaTime;
        if (p.life > 0.0){
            p.position += p.velocity*deltaTime;
//            p.testColor.a -= deltaTime * 0.01f;
        }
    }
}

void ParticleSystem::updateDis(float deltaTime, BoundingSphere *astro, unsigned int newParticles)
{
    for (unsigned int i = 0; i < newParticles; ++i)
    {
        int unusedParticle = this->firstUnusedParticle();
        this->spawnParticles(astro, &particles[unusedParticle]);
    }
    
    for (unsigned int i = 0; i < MAX_PARTICLES; ++i){
        Particle &p = particles[i];
        p.life -= deltaTime;
        if (p.life > 0.0){
            p.position -= p.velocity*deltaTime;
        }
    }
}

void ParticleSystem::spawnParticles(BoundingSphere* astro, Particle * particle)
{
    float randX = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/1));
    float randDeg = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/360));
//    float rColor = 0.5f + ((rand() % 100) / 100.0f);
//    particle.color = glm::vec3(rColor);
//    glm::vec3 dirc = glm::vec3(astro->center.x+randX, astro->center.y, astro->center.z);
    glm::vec3 dirc = glm::vec3(randX,0,0);
    
//    glm::mat4 transMatrix = glm::mat4(1);
//    transMatrix = glm::translate(transMatrix, glm::vec3(randX,0,0));
//    dirc = glm::vec3(transMatrix * glm::rotate(glm::radians(randDeg), glm::vec3(0,1,0)) * inverse(transMatrix) * glm::vec4(dirc,1.0));
    
    dirc = glm::vec3(glm::rotate(glm::mat4(1), glm::radians(randDeg), glm::vec3(0,1,0)) * glm::vec4(dirc, 1.0));
    
    particle->position = dirc;
//    particle->position = astro->center;
    particle->life = 1.0f;
    
    float randColor = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/1));
    particle->color = glm::vec3(randColor);
//    particle->velocity = glm::length(particle->position) * 0.1f;
    particle->velocity = particle->position * 0.1f;
    particle->testColor = glm::vec4(1,1,0,1.0);
//    glm::vec3 vel = glm::vec3(1,0,0);
//    particle->velocity = glm::length(glm::vec3(glm::rotate(glm::mat4(1), randDeg, glm::vec3(0,1,0))* glm::vec4(vel,1.0))) * 0.1f;
}

unsigned int lastUsedParticle = 0;
unsigned int ParticleSystem::firstUnusedParticle()
{
    for (unsigned int i = lastUsedParticle; i < MAX_PARTICLES; ++i){
        if (particles[i].life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    
    for (unsigned int i = 0; i < lastUsedParticle; ++i){
        if (particles[i].life <= 0.0f){
            lastUsedParticle = i;
            return i;
        }
    }
    
    lastUsedParticle = 0;
    return 0;
}
