//
//  BoundingSphere.hpp
//  CSE167-project1
//
//  Created by siyu meng on 12/2/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#ifndef BoundingSphere_hpp
#define BoundingSphere_hpp

#include <stdio.h>
#include "Object.h"
#include "Transform.hpp"

using namespace std;

class BoundingSphere
{
  public:
    BoundingSphere();
    ~BoundingSphere();
    std::vector<BoundingSphere*> allBoundingsphere;
    std::vector<BoundingSphere*> allBoundingWall;
    float radius;
    glm::vec3 center;
    float dist;
    glm::vec3 normalV;
    int isBox;
    Transform* mod;
    int isRender = 1;
    
    
    glm::vec3 direction = glm::vec3(0,0,1);
    
    void createBounding(glm::mat4 modelMatrix);
    
    void addSphere(BoundingSphere * sphere)
    {
        allBoundingsphere.push_back(sphere);
    }
    void addWall(BoundingSphere * wall)
    {
        allBoundingWall.push_back(wall);
    }
    
    bool checkCollisionSphere(BoundingSphere* astro, BoundingSphere* ball);
    bool checkCollisionWall(BoundingSphere* astro, BoundingSphere* wall);
    
    void setDirt(glm::vec3 newDirt)
    {
        direction = newDirt;
    }
};

#endif /* BoundingSphere_hpp */
