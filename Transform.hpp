//
//  Transfore.hpp
//  CSE167-project1
//
//  Created by siyu meng on 11/14/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#ifndef Transform_hpp
#define Transform_hpp

#include <stdio.h>
#include "Node.h"

class Transform : public Node
{
public:
    glm::mat4 matrixM;
    std::vector<Node*> childsNode;
    Transform * parent;
    
    Transform(glm::mat4 matrixMP);
    ~Transform();
    
    void addChild(Node* child);
    void draw(const glm::mat4& matrixC);
    void update(const int isRotate, const int isCenter, const int isUpdown);
    void updown(glm::vec3 move);
    void spin(float deg);
    void around(float deg);
    int isUp = 1;
    int counter = 0;
    
};

#endif /* Transfore_hpp */
