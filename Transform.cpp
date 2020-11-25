//
//  Transfore.cpp
//  CSE167-project1
//
//  Created by siyu meng on 11/14/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#include "Transform.hpp"

Transform::Transform(glm::mat4 matrixMP)
{
    matrixM = matrixMP;
}

Transform::~Transform()
{
    
}


void Transform::addChild(Node* child)
{
    childsNode.push_back(child);
    child->parent = this;
}


void Transform::draw(const glm::mat4 &matrixC)
{
    glm::mat4 new_M = matrixC * matrixM;
    for (auto& node : childsNode)
    {
        node->draw(new_M);
    }
}

void Transform::update(const int isRotate, const int isCenter, const int isUpdown)
{
    //glm::mat4 new_M = matrixC * matrixM;

    if(isRotate == 1){
        for (auto& node : this->childsNode)
        {
            node -> spin(0.1);
        }
    }
    
    if(isCenter == 1){
        around(0.1);
    }
    
    if(isUpdown == 1){
        if(isUp == 1){
            updown(glm::vec3(0,0.001,0));
            counter = counter + 1;
        }
        else{
            updown(glm::vec3(0,-0.001,0));
            counter = counter - 1;
        }
    }
}

void Transform::updown(glm::vec3 move)
{
    if (counter == 2000) {
        isUp = 0;
    }
    else if (counter == 0)
    {
        isUp = 1;
    }
    matrixM = glm::translate(move) * matrixM;
}

void Transform::spin(float deg)
{
    matrixM = matrixM * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Transform::around(float deg)
{
    //glm::vec3 pointT = glm::vec3(3.322739,59.872997,4.617175);
    //glm::vec3 pointC = glm::vec3(-0.000000,0.000000,-0.750000);
    glm::vec3 origin = glm::vec3(28,0,0);
    //glm::vec3 axis = glm::cross(pointT, pointC);
    glm::mat4 translate = glm::translate(glm::mat4(1), origin);
    matrixM = translate * glm::rotate(glm::mat4(1), glm::radians(deg), glm::vec3(0,1,0)) * inverse(translate) * matrixM;

    
    /*
    matrixM = matrixM * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
    matrixM = matrixM * glm::translate(glm::vec3(0.05,0,0));
    matrixM = matrixM * glm::rotate(glm::radians(deg), glm::vec3(0,1,0));
     */
     
}
