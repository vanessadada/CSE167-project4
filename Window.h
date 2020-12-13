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
#include "BoundingSphere.hpp"
#include "ParticleSystem.hpp"
#include <iostream>
#include <vector>

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
    static Transform * teapot1;
    static Transform * teapot2;
    static Geometry * coneModel;
    static Geometry * cy1model;
    static Geometry * te1model;
    static Geometry * te2model;

    static Transform * lobbyRoot;
    static Transform * astroStandChild;
    static Transform * astroStand1Child;
    static Transform * astroStand2Child;
    static Transform * astroStand3Child;
    static Transform * astroStand4Child;
    
    static Geometry * lobby;
    static Geometry * astroStand;
    static Geometry * astroStand1;
    static Geometry * astroStand2;
    static Geometry * astroStand3;
    static Geometry * astroStand4;
    
    static BoundingSphere * box1;
    static BoundingSphere * box2;
    static BoundingSphere * a;
    static BoundingSphere * a1;
    static BoundingSphere * a2;
    static BoundingSphere * a3;
    static BoundingSphere * a4;
    static BoundingSphere * frontWall;
    static BoundingSphere * backStair;
    static BoundingSphere * leftWall;
    static BoundingSphere * rightWall;
    static BoundingSphere * leftDiag;
    static BoundingSphere * rightDiag;

    static ParticleSystem * partAppear;
    static ParticleSystem * partAppear1;
    static ParticleSystem * partAppear2;
    static ParticleSystem * partAppear3;
    
    static ParticleSystem * partDis;
    static ParticleSystem * partDis1;
    static ParticleSystem * partDis2;
    static ParticleSystem * partDis3;
    
    static Geometry * astroMove1;
    static Geometry * astroMove2;
    
    
    static glm::vec3 lastpoint;

	// Camera Matrices
	static glm::mat4 projection;
	static glm::mat4 view;
	static glm::vec3 eyePos, lookAtPoint, upVector, frontVector;

	// Shader Program ID
	static GLuint shaderProgram;
    static GLuint sphereShader;
    static GLuint modelShader;
    static GLuint toonShader;
    static GLuint particleShader;

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
    static void move(Transform* astro, BoundingSphere* a);
};

#endif
