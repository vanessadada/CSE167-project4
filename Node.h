//
//  Node.hpp
//  CSE167-project1
//
//  Created by siyu meng on 11/14/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#ifndef Node_h
#define Node_h

#include <stdio.h>
#include "Object.h"

class Node
{
public:
    Node* parent;
    
    virtual void draw(const glm::mat4& matrixC)=0;
    virtual void update(const float time)=0;
    virtual void spin(const float deg) = 0;
};

#endif /* Node_hpp */
