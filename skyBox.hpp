//
//  skyBox.hpp
//  CSE167-project1
//
//  Created by siyu meng on 11/11/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#ifndef skyBox_hpp
#define skyBox_hpp

#include <stdio.h>
#include "Object.h"

#include <vector>
#include <stdio.h>

using namespace std;

class skyBox: public Object
{
private:
    GLuint skyboxVAO;
    GLuint skyboxVBO;
    GLuint skyboxEBO;
    
public:
   skyBox(std::string objFilenameF, std::string objFilenameB, std::string objFilenameR, std::string objFilenameL, std::string objFilenameBT, std::string objFilenameTP);
    ~skyBox();
    
    unsigned int cubemapTexture;
    unsigned int loadCubemap(vector<std::string> faces);
    void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader);
    void update();
    void spin(float deg);
};

#endif /* skyBox_hpp */
