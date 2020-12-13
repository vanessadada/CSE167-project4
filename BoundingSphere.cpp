//
//  BoundingSphere.cpp
//  CSE167-project1
//
//  Created by siyu meng on 12/2/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#include "BoundingSphere.hpp"

BoundingSphere::BoundingSphere()
{
    
}
BoundingSphere::~BoundingSphere()
{
    
}

void BoundingSphere::createBounding(glm::mat4 modelMatrix)
{
    center = modelMatrix[3];
    glm::vec4 tempM = modelMatrix * glm::vec4(7,0,0,0);
    radius = length(tempM);
}

bool BoundingSphere::checkCollisionSphere(BoundingSphere* astro, BoundingSphere* ball)
{
    float distance = length(astro->center - ball->center);
    float twoRadius = astro->radius + ball->radius;
    return distance < twoRadius;
}

bool BoundingSphere::checkCollisionWall(BoundingSphere* astro, BoundingSphere* wall)
{
    float distance = dot(astro->center, wall->normalV) - wall->dist;
    return distance <= astro->radius;
}
