#ifndef _POINT_CLOUD_H_
#define _POINT_CLOUD_H_

#include "Object.h"

#include <vector>
#include <string>

using namespace std;

class PointCloud : public Object
{
private:
	std::vector<glm::vec3> points;
    std::vector<glm::vec3> normals;
    std::vector<glm::ivec3> faces;

	GLuint VAO, VBO;
    //GLuint lVAO;
    GLuint EBO;
	GLfloat pointSize;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
    int type;
    
    GLuint nVBO;
    int indicator;
    float linear = 100;

public:
	PointCloud(std::string objFilename, GLfloat pointSize, glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess, int type);
	~PointCloud();
	
	void draw(const glm::mat4& view, const glm::mat4& projection, GLuint shader, glm::vec3 lightPos);
	void update();
    void rotateL(float angle, glm::vec3 axis);

	void updatePointSize(GLfloat size);
    void switchIndicator();
	void spin(float deg);
    
    void scale(double size);
};

#endif
