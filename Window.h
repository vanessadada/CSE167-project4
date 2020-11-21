#ifndef _WINDOW_H_
#define _WINDOW_H_

#include "main.h"
#include "shader.h"
#include "Object.h"
#include "Cube.h"
#include "PointCloud.h"
#include "skyBox.hpp"
#include "Sphere.h"
#include "Transform.hpp"
#include "Geometry.hpp"
#include "Node.h"


class Window
{
public:

	// Window Properties
	static int width;
	static int height;
	static const char* windowTitle;

	// Objects to Render
	static Cube* cube;
	static PointCloud * cubePoints;
    
    
    
    static skyBox * skybox;
    static Sphere * sphere;
    static Transform * cone;
    static Transform * cylinder1;
    static Transform * cylinder2;
    static Transform * cylinder3;
    static Transform * cylinder4;
    static Transform * cylinder5;
    static Transform * cylinder6;
    static Transform * teapot1;
    static Transform * teapot2;
    static Transform * teapot3;
    static Transform * teapot4;
    static Transform * teapot5;
    static Transform * teapot6;
    static Geometry * coneModel;
    static Geometry * cy1model;
    static Geometry * te1model;
    static Geometry * te2model;
    
    
    
    static glm::vec3 lastpoint;

	// Camera Matrices
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 eyePos, lookAtPoint, upVector, frontVector;

	// Shader Program ID
	static GLuint shaderProgram;
    static GLuint sphereShader;
    static GLuint modelShader;

	// Constructors and Destructors
	static bool initializeProgram();
	static bool initializeObjects();
	static void cleanUp();

	// Window functions
	static GLFWwindow* createWindow(int width, int height);
	static void resizeCallback(GLFWwindow* window, int width, int height);

	// Draw and Update functions
	static void idleCallback();
	static void displayCallback(GLFWwindow*);

	// Callbacks
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
    static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
    static glm::vec3 rotate(double x, double y);
};

#endif
