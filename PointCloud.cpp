#include "PointCloud.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdio.h>


PointCloud::PointCloud(std::string objFilename, GLfloat pointSize, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, int type)
	: pointSize(pointSize), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess), type(type)
{
	/* 
	 * TODO: Section 2: Currently, all the points are hard coded below. 
	 * Modify this to read points from an obj file.
	 */
	std::ifstream objFile(objFilename); // The obj file we are reading.
    
    // Check whether the file can be opened.
    if (objFile.is_open())
    {
        std::string line; // A line in the file.

        // Read lines from the file.
        while (std::getline(objFile, line))
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
                    std::string delimiter = "//";
                    std::string x = token.substr(0, token.find(delimiter));
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
    else
    {
        std::cerr << "Can't open the file " << objFilename << std::endl;
    }

    objFile.close();
    

	/*
	 * TODO: Section 4, you will need to normalize the object to fit in the
	 * screen. 
	 */
    
    if (type == 1){
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
        // Set the model matrix to an identity matrix.
        model = glm::mat4(1);
        color = glm::vec3(220, 220, 220);
        lightPos = glm::vec3(6,6,6);
    }
    else{
        lightPos = glm::vec3(6,6,6);
        model = glm::mat4(1);
        model = glm::translate(glm::mat4(1), lightPos)*model;
        model = glm::scale(model, glm::vec3(0.25));
    }

	// Set the color.
    lightcolor = glm::vec3(1, 0, 1);
    viewPos = glm::vec3(0, 0, 20);
    ambientlight = diffuselight * glm::vec3(0.2);
    diffuselight = lightcolor * glm::vec3(0.5);
    specularlight = glm::vec3(1.0,1.0,1.0);
    
	// Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
	glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &nVBO);
    
	glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO to the bound VAO, and store the point data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, nVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);
	// Enable Vertex Attribute 0 to pass point data through to the shader

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

    /*glGenVertexArrays(1, &lVAO);
    glBindVertexArray(lVAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);
    */
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(glm::ivec3) * faces.size(), faces.data(), GL_STATIC_DRAW);
    
	// Unbind the VBO/VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

PointCloud::~PointCloud() 
{
	// Delete the VBO and the VAO.
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &EBO);
}

void PointCloud::rotateL (float angle, glm::vec3 axis){
        glm::vec3 origin = glm::vec3(0,0,0);
        glm::mat4 translate = glm::translate(glm::mat4(1), origin);
        lightPos = glm::vec3(translate * glm::rotate(glm::mat4(1), angle, axis) * inverse(translate) * glm::vec4(lightPos,1));
        
        model = translate * glm::rotate(glm::mat4(1), angle, axis)* inverse(translate) * model;
        
        //lightPos = model[3];
    }

void PointCloud::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader, glm::vec3 lightPos)
{
	// Actiavte the shader program 
	glUseProgram(shader);

	// Get the shader variable locations and send the uniform data to the shader 
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));
    
    glUniform3fv(glGetUniformLocation(shader, "lightcolor"), 1, glm::value_ptr(lightcolor));
    
    glUniform3fv(glGetUniformLocation(shader, "viewPos"), 1, glm::value_ptr(viewPos));
    
    glUniform3fv(glGetUniformLocation(shader, "material.ambient"), 1, glm::value_ptr(ambient));

    glUniform3fv(glGetUniformLocation(shader, "material.diffuse"), 1, glm::value_ptr(diffuse));
    
    glUniform3fv(glGetUniformLocation(shader, "material.specular"), 1, glm::value_ptr(specular));
    
    glUniform1f(glGetUniformLocation(shader, "material.shininess"), shininess);
    
    glUniform1i(glGetUniformLocation(shader, "indicator"), indicator);
    
    glUniform1i(glGetUniformLocation(shader, "type"), type);
    
    glUniform1f(glGetUniformLocation(shader, "light.linear"), linear);
    
    glUniform3fv(glGetUniformLocation(shader, "light.position"), 1, glm::value_ptr(lightPos));
    
    glUniform3fv(glGetUniformLocation(shader, "light.ambient"), 1, glm::value_ptr(ambientlight));
    
    glUniform3fv(glGetUniformLocation(shader, "light.diffuse"), 1, glm::value_ptr(diffuselight));
	
    glUniform3fv(glGetUniformLocation(shader, "light.specular"), 1, glm::value_ptr(specularlight));
    // Bind the VAO
	glBindVertexArray(VAO);
    //glBindVertexArray(lVAO);

	// Set point size
	glPointSize(pointSize);
    
    glDrawElements(GL_TRIANGLES, (3 * faces.size()), GL_UNSIGNED_INT, 0);
    
	// Unbind the VAO and shader program
	glBindVertexArray(0);
	glUseProgram(0);
}

void PointCloud::update()
{
	// Spin the cube by 1 degree
	spin(0.1f);
}

void PointCloud::updatePointSize(GLfloat size) 
{
	/*
	 * TODO: Section 3: Implement this function to adjust the point size.
	 */
    
    pointSize = size;
}

void PointCloud::switchIndicator()
{
    if(indicator == 1){
        indicator = 0;
    }
    else{
        indicator = 1;
    }
}

void PointCloud::scale(double x)
{
    if(type == 1){
        model = glm::scale(model, glm::vec3(x));
    }
    else{
        glm::vec3 origin = glm::vec3(0,0,0);
        glm::mat4 translate = glm::translate(glm::mat4(1), origin);
        model = translate * glm::scale(glm::vec3(x)) * inverse(translate) * model;
    }
}

void PointCloud::spin(float deg)
{
	// Update the model matrix by multiplying a rotation matrix
	//model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}
