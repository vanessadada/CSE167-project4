//
//  Geometry.cpp
//  CSE167-project1
//
//  Created by siyu meng on 11/14/20.
//  Copyright © 2020 siyu meng. All rights reserved.
//

#include "Geometry.hpp"

Geometry::Geometry(std::string filename, glm::vec3 color, glm::vec3 positionP, glm::vec3 sizeP, int isCylinderP, float degP)
{
    isCylinder = isCylinderP;
    init(filename);
    modelColor = color;
    position = positionP;
    size = sizeP;
    deg = degP;
}

Geometry::~Geometry()
{
    
}

void Geometry::init(std::string filename)
{
    modelG = glm::mat4(1);
    modelG = glm::scale(modelG, glm::vec3(0.5));
    
    std::ifstream objFile(filename); // The obj file we are reading.
    
    std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
    std::vector< glm::vec3 > temp_vertices;
    std::vector< glm::vec2 > temp_uvs;
    std::vector< glm::vec3 > temp_normals;
    
    // Check whether the file can be opened.
    if (objFile.is_open())
    {
        std::string line; // A line in the file.
        // Read lines from the file.
        while (std::getline(objFile, line))
        {
            if(isCylinder == 1){
                std::stringstream ss;
                ss << line;
                std::string label;
                ss >> label;
                
                if (label == "v")
                {
                    // Read the later three float numbers and use them as the
                    // coordinates.
                    glm::vec3 point;
                    ss >> point.x >> point.y >> point.z;

                    // Process the point. For example, you can save it to a.
                    temp_vertices.push_back(point);
                }
                
                if(label == "vn")
                {
                    glm::vec3 normal;
                    ss >> normal.x >> normal.y >> normal.z;
                    temp_normals.push_back(normal);
                }
                
                std::string token;
                std::string xyz;
                if(label == "f")
                {
                    std::string vertex1, vertex2, vertex3;
                    unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
                    /*
                    int i = 0;
                    while(std::getline(ss, token, ' ')) {
                        std::string x;
                        std::string delimiter = "/";
                        unsigned int first = token.find(delimiter);
                        unsigned int last = token.find_last_of(delimiter);
                        std::string v0 = token.substr(0, first);
                        std::string u0 = token.substr(first+1, last);
                        std::string n0 = token.substr(last+1, last+2);
                        unsigned int indexv;
                        sscanf(v0.c_str(), "%d", &indexv);
                        unsigned int indexu;
                        sscanf(u0.c_str(), "%d", &indexu);
                        unsigned int indexn;
                        sscanf(n0.c_str(), "%d", &indexn);
                        
                        vertexIndex[i] = indexv;
                        uvIndex[i] = indexu;
                        normalIndex[i] = indexn;
                        
                        i +=1;
                    }
                     */
                    //std::cerr<<ss.str().c_str()<<std::endl;
                    std::string x;
                    sscanf(ss.str().c_str(), "%s %d/%d/%d %d/%d/%d %d/%d/%d\n", &x, &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);

                    //std::cerr<<vertexIndex[1]<<std::endl;
                    
                    vertexIndices.push_back(vertexIndex[0]);
                    vertexIndices.push_back(vertexIndex[1]);
                    vertexIndices.push_back(vertexIndex[2]);
                    normalIndices.push_back(normalIndex[0]);
                    normalIndices.push_back(normalIndex[1]);
                    normalIndices.push_back(normalIndex[2]);
                }
            }
            else
            {
                // Turn the line into a string stream for processing.
                std::stringstream ss;
                ss << line;
            
                // Read the first word of the line.
                std::string label;
                ss >> label;
                
                // If the line is about vertex (starting with a "v").
                if (label == "v")
                {
                    // Read the later three float numbers and use them as the
                    // coordinates.
                    glm::vec3 point;
                    ss >> point.x >> point.y >> point.z;

                    // Process the point. For example, you can save it to a.
                    points.push_back(point);
                }
                
                if(label == "vn")
                {
                    glm::vec3 normal;
                    ss >> normal.x >> normal.y >> normal.z;
                    normals.push_back(normal);
                }
                
                std::string token;
                std::string xyz;
                if(label == "f")
                {
                        while(std::getline(ss, token, ' ')) {
                            std::string x;
                            std::string delimiter = "//";
                            x = token.substr(0, token.find(delimiter));
                            xyz.append(x);
                            xyz.append(" ");
                        }
                    
                        std::stringstream ind (xyz);
                        glm::ivec3 indice;
                        ind >> indice.x >> indice.y >> indice.z;
                        indice.x = indice.x-1;
                        indice.y = indice.y-1;
                        indice.z = indice.z-1;
                        faces.push_back(indice);
                }
            }
        }
    }
    else
    {
        std::cerr << "Can't open the file " << filename << std::endl;
    }

    objFile.close();
    
    if(isCylinder == 1){
        for( unsigned int i=0; i<vertexIndices.size(); i++ ){
            unsigned int vertexIndex = vertexIndices[i];
            //std::cerr<<vertexIndex<<std::endl;
            glm::vec3 vertex = temp_vertices[vertexIndex-1];
            //std::cerr<<vertex.x<<std::endl;
            points.push_back(vertex);
            
            unsigned int normalIndex = normalIndices[i];
            glm::vec3 normal = temp_normals[normalIndex-1];
            normals.push_back(normal);
        }
        
        for (unsigned int j = 0; j< vertexIndices.size(); j++){
            glm::ivec3 indice = glm::ivec3(j,j+1,j+2);
            faces.push_back(indice);
            j = 2+j;
        }
    }
    
    
    std::vector<float> xarray;
    std::vector<float> yarray;
    std::vector<float> zarray;

    for(auto& p : points)
    {
        xarray.push_back(p.x);
        yarray.push_back(p.y);
        zarray.push_back(p.z);
    }
    

    float xmin = *min_element(xarray.begin(), xarray.end());
    float ymin = *min_element(yarray.begin(), yarray.end());
    float zmin = *min_element(zarray.begin(), zarray.end());
    
    float xmax = *max_element(xarray.begin(), xarray.end());
    float ymax = *max_element(yarray.begin(), yarray.end());
    float zmax = *max_element(zarray.begin(), zarray.end());
    
    float xcenter = (xmax+xmin)/2;
    float ycenter = (ymax+ymin)/2;
    float zcenter = (zmax+zmin)/2;
    
    for(auto& p : points)
    {
        p.x = p.x - xcenter;
        p.y = p.y - ycenter;
        p.z = p.z - zcenter;
    }

    std::vector<float> xarrayC;
    std::vector<float> yarrayC;
    std::vector<float> zarrayC;

    for(auto& p : points)
    {
        xarrayC.push_back(abs(p.x));
        yarrayC.push_back(abs(p.y));
        zarrayC.push_back(abs(p.z));
    }
    
    float xmaxC = *max_element(xarrayC.begin(), xarrayC.end());
    float ymaxC = *max_element(yarrayC.begin(), yarrayC.end());
    float zmaxC = *max_element(zarrayC.begin(), zarrayC.end());
    float maxAll = std::max(xmaxC, ymaxC);
    maxAll = std::max(maxAll, zmaxC);
    
    float factor = 7/maxAll;

    for(auto& p : points)
    {
        p.x = p.x*factor;
        p.y = p.y*factor;
        p.z = p.z*factor;
    }
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &nVBO);
    glGenBuffers(1, &VBO);
    
    glBindVertexArray(VAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), &points[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, nVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), &normals[0], GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * faces.size(), faces.data(), GL_STATIC_DRAW);
    
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Geometry::draw(const glm::mat4 &matrixC)
{
    //modelMatrix = matrixC;
    setMatrix(matrixC);
    renderModel(viewMatirx, modelProjection, shaderProgram);
}

void Geometry::renderModel(glm::mat4 &view, glm::mat4 &projection, GLuint shader)
{
    glUseProgram(shader);
    
    glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
    glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
    glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(modelG));
    glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(modelColor));
    
    
    glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(cameraPos));
    glUniform3fv(glGetUniformLocation(shader, "light.position"), 1, glm::value_ptr(lightPos));
    glUniform3fv(glGetUniformLocation(shader, "light.lightcolor"), 1, glm::value_ptr(lightColor));
    glUniform1f(glGetUniformLocation(shader, "light.linear"), 0.09);
    
    glUniform3fv(glGetUniformLocation(shader, "material.ambient"), 1, glm::value_ptr(ambient));
    
    glUniform3fv(glGetUniformLocation(shader, "material.diffuse"), 1, glm::value_ptr(diffuse));
        
    glUniform3fv(glGetUniformLocation(shader, "material.specular"), 1, glm::value_ptr(specular));
        
    glUniform1f(glGetUniformLocation(shader, "material.shininess"), shininess);
        
    
    glBindVertexArray(VAO);
    
    glDrawElements(GL_TRIANGLES, (3 * faces.size()), GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    
    glUseProgram(0);
}

void Geometry::update(const int isRotate, const int isCenter, const int isUpdown)
{
    //setMatrix(matrixC);
    if (isRotate == 1){
        spin(0.1);
    }
    
    if (isCenter == 1){
        around(0.1);
    }
}

void Geometry::spin(float deg)
{
    modelG = modelG * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}

void Geometry::setMatrix(glm::mat4 modelView)
{
    modelG = modelView;
    modelG = glm::translate(glm::mat4(1), position) * modelG;
    modelG = glm::scale(glm::mat4(1), size) * modelG;
    //modelG = glm::rotate(glm::mat4(1), deg, glm::vec3(1,0,0)) * modelG;
}

void Geometry::around(float deg)
{
    //glm::vec3 pointT = glm::vec3(3.322739,59.872997,4.617175);
    //glm::vec3 pointC = glm::vec3(-0.000000,0.000000,-0.750000);
    glm::vec3 origin = glm::vec3(15,0,0);
    //glm::vec3 axis = glm::cross(pointT, pointC);
    glm::mat4 translate = glm::translate(glm::mat4(1), origin);
    modelG = translate * glm::rotate(glm::mat4(1), glm::radians(deg), glm::vec3(0,1,0)) * inverse(translate) * modelG;

    
    /*
    matrixM = matrixM * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
    matrixM = matrixM * glm::translate(glm::vec3(0.05,0,0));
    matrixM = matrixM * glm::rotate(glm::radians(deg), glm::vec3(0,1,0));
     */
     
}
