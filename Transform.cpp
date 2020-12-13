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

void Transform::update(const float time)
{
//    for (auto& node : this->childsNode)
//        {
//            node -> update(time);
//        }
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

void Transform::move(float time)
{
     matrixM = matrixM * glm::translate(glm::mat4(1), glm::vec3(0,0,3));
}

void Transform::scale(double x){
    matrixM = glm::scale(matrixM, glm::vec3(x));
}
