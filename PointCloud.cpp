#include "PointCloud.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>


PointCloud::PointCloud(std::string objFilename, GLfloat pointSize) 
	: pointSize(pointSize)
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
        }
    }
    else
    {
        std::cerr << "Can't open the file " << objFilename << std::endl;
    }

    objFile.close();
    
    /*
	points = {
		glm::vec3(-2.5, 2.5, 2.5),
		glm::vec3(-2.5, -2.5, 2.5),
		glm::vec3(2.5, -2.5, 2.5),
		glm::vec3(2.5, 2.5, 2.5),
		glm::vec3(-2.5, 2.5, -2.5),
		glm::vec3(-2.5, -2.5, -2.5),
		glm::vec3(2.5, -2.5, -2.5),
		glm::vec3(2.5, 2.5, -2.5)
	};*/

	/*
	 * TODO: Section 4, you will need to normalize the object to fit in the
	 * screen. 
	 */
    
    
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

	// Set the color. 
	color = glm::vec3(0, 0, 1);

	// Generate a Vertex Array (VAO) and Vertex Buffer Object (VBO)
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// Bind VAO
	glBindVertexArray(VAO);

	// Bind VBO to the bound VAO, and store the point data
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * points.size(), points.data(), GL_STATIC_DRAW);
	// Enable Vertex Attribute 0 to pass point data through to the shader
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), 0);

	// Unbind the VBO/VAO
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

PointCloud::~PointCloud() 
{
	// Delete the VBO and the VAO.
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void PointCloud::draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader)
{
	// Actiavte the shader program 
	glUseProgram(shader);

	// Get the shader variable locations and send the uniform data to the shader 
	glUniformMatrix4fv(glGetUniformLocation(shader, "view"), 1, false, glm::value_ptr(view));
	glUniformMatrix4fv(glGetUniformLocation(shader, "projection"), 1, false, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform3fv(glGetUniformLocation(shader, "color"), 1, glm::value_ptr(color));

	// Bind the VAO
	glBindVertexArray(VAO);

	// Set point size
	glPointSize(pointSize);
    
    //std::cout<<points.size();
	// Draw the points 
	glDrawArrays(GL_POINTS, 0, points.size());

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

void PointCloud::spin(float deg)
{
	// Update the model matrix by multiplying a rotation matrix
	model = model * glm::rotate(glm::radians(deg), glm::vec3(0.0f, 1.0f, 0.0f));
}
