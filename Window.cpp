#include "Window.h"

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "GLFW Starter Project";
const double m_ROTSCALE = 90.0;
bool but = false;
int sOr = 1;

// Objects to Render
Cube * Window::cube;
PointCloud * Window::cubePoints;
//Object* currObj;
PointCloud * currObj;

//
PointCloud * Window::bearPoints;
PointCloud * Window::bunnyPoints;
PointCloud * Window::sandalPoints;
PointCloud * Window::lightSource;
glm::vec3 Window::lastpoint(0,0,0);

// Camera Matrices 
// Projection matrix:
glm::mat4 Window::projection; 

// View Matrix:
glm::vec3 Window::eyePos(0, 0, 20);			// Camera position.
glm::vec3 Window::lookAtPoint(0, 0, 0);		// The point we are looking at.
glm::vec3 Window::upVector(0, 1, 0);		// The up direction of the camera.
glm::mat4 Window::view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

// Shader Program ID
GLuint Window::shaderProgram; 



bool Window::initializeProgram() {
	// Create a shader program with a vertex shader and a fragment shader.
	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");

	// Check the shader program.
	if (!shaderProgram)
	{
		std::cerr << "Failed to initialize shader program" << std::endl;
		return false;
	}

	return true;
}

bool Window::initializeObjects()
{
	// Create a cube of size 5.
	//cube = new Cube(5.0f);

	// Create a point cloud consisting of cube vertices.
	//cubePoints = new PointCloud("foo", 100);

    bearPoints = new PointCloud("bear.obj", 5, glm::vec3 (0,0,0
                                                          ), glm::vec3 (0,0,0), glm::vec3 (100,100,100), 0.25, 1);
    
    bunnyPoints = new PointCloud("bunny.obj", 5, glm::vec3 (0.2,0.2,0.2), glm::vec3 (10,10,10), glm::vec3 (0,0,0), 0.25, 1);
    
    sandalPoints = new PointCloud("SandalF20.obj", 5, glm::vec3 (0.25,0.20725,0.20725), glm::vec3 (1,0.829,0.829), glm::vec3 (0.6,0.7,0.7), 0.088, 1);
    
    lightSource = new PointCloud("sphere.obj", 5, glm::vec3(1,0,1), glm::vec3(0,0,0), glm::vec3(0,0,0), 0.25, 0);
 
	// Setcube to be the first to display
	//currObj = cube;
    
    currObj = sandalPoints;
    
	return true;
}

void Window::cleanUp()
{
	// Deallcoate the objects.
	//delete cube;
	//delete cubePoints;
    
    delete bearPoints;
    delete bunnyPoints;
    delete sandalPoints;
	// Delete the shader program.
	glDeleteProgram(shaderProgram);
}

GLFWwindow* Window::createWindow(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cerr << "Failed to initialize GLFW" << std::endl;
		return NULL;
	}

	// 4x antialiasing.
	glfwWindowHint(GLFW_SAMPLES, 4);

#ifdef __APPLE__ 
	// Apple implements its own version of OpenGL and requires special treatments
	// to make it uses modern OpenGL.

	// Ensure that minimum OpenGL version is 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Enable forward compatibility and allow a modern OpenGL context
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// Create the GLFW window.
	GLFWwindow* window = glfwCreateWindow(width, height, windowTitle, NULL, NULL);

	// Check if the window could not be created.
	if (!window)
	{
		std::cerr << "Failed to open GLFW window." << std::endl;
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window.
	glfwMakeContextCurrent(window);

#ifndef __APPLE__
	// On Windows and Linux, we need GLEW to provide modern OpenGL functionality.

	// Initialize GLEW.
	if (glewInit())
	{
		std::cerr << "Failed to initialize GLEW" << std::endl;
		return NULL;
	}
#endif

	// Set swap interval to 1.
	glfwSwapInterval(0);

	// Call the resize callback to make sure things get drawn immediately.
	Window::resizeCallback(window, width, height);

	return window;
}

void Window::resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	// In case your Mac has a retina display.
	glfwGetFramebufferSize(window, &width, &height); 
#endif
	Window::width = width;
	Window::height = height;
	// Set the viewport size.
	glViewport(0, 0, width, height);

	// Set the projection matrix.
	Window::projection = glm::perspective(glm::radians(60.0), 
								double(width) / (double)height, 1.0, 1000.0);
}

void Window::idleCallback()
{
	// Perform any necessary updates here 
	currObj->update();
}

void Window::displayCallback(GLFWwindow* window)
{	
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	

	// Render the objects
    lightSource->draw(view, projection, shaderProgram, lightSource->model[3]);
	currObj->draw(view, projection, shaderProgram, lightSource->model[3]);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();

	// Swap buffers.
	glfwSwapBuffers(window);
}

void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	/*
	 * TODO: Modify below to add your key callbacks.
	 */
	
	// Check for a key press.
	if (action == GLFW_PRESS)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);				
			break;

		// switch between the cube and the cube pointCloud
		case GLFW_KEY_1:
                sOr = 1;
			break;
		case GLFW_KEY_2:
                sOr = 2;
			break;
        case GLFW_KEY_3:
                sOr = 0;
            break;
        case GLFW_KEY_A:
                currObj = sandalPoints;
            break;
        case GLFW_KEY_B:
                currObj = bunnyPoints;
            break;
        case GLFW_KEY_C:
                currObj = bearPoints;
            break;
        case GLFW_KEY_L:
                currObj->updatePointSize(100);
            break;
        case GLFW_KEY_S:
                currObj->updatePointSize(1);
            break;
        case GLFW_KEY_N:
                currObj->switchIndicator();
		default:
			break;
		}
	}
}

void Window::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT){
        if(action == GLFW_PRESS) {
            if(lastpoint == glm::vec3(0,0,0)){
                double x, y;
                glfwGetCursorPos(window, &x, &y);
                lastpoint = rotate(x, y);
            }
            but = true;
        }
        if(action == GLFW_RELEASE){
            but = false;
        }
    }
}

void Window::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    if(but == true){
        glm::vec3 direction;
        float rot_angle;
        glm::vec3 curPoint;
    
        curPoint = rotate(xpos, ypos);
        //direction = curPoint - lastpoint;
        direction = lastpoint - curPoint;
        float velocity = direction.length();
        
        if(velocity > 0.01){
            glm::vec3 rotAxis;
            rotAxis = glm::cross(curPoint, lastpoint);
            //rotAxis = glm::cross(lastpoint, curPoint);
            rot_angle = velocity * m_ROTSCALE;
            if(sOr == 1){
                currObj->model = glm::rotate(glm::mat4(1), rot_angle, rotAxis)*currObj->model;
            }
            else if (sOr == 2){
                lightSource->rotateL(rot_angle, rotAxis);
            }
            else{
                currObj->model = glm::rotate(glm::mat4(1), rot_angle, rotAxis)*currObj->model;
                lightSource->rotateL(rot_angle, rotAxis);
            }
        }
        lastpoint = curPoint;
    }
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    if(sOr == 1){
        yoffset = 1 + yoffset;
        currObj->scale(yoffset);
    }
    else if(sOr == 2){
        yoffset = 1 + yoffset;
        lightSource->scale(yoffset);
    }
    else{
        yoffset = 1 + yoffset;
        currObj->scale(yoffset);
        lightSource->scale(yoffset);
        
    }
    
    
}

glm::vec3 Window::rotate(double x, double y)
{
    glm::vec3 v;
    float d;
    v.x = (2.0*x- width) / width;
    v.y = (height - 2.0*y) / height;
    v.z = 0.0;
    d = glm::length(v);
    d = (d<1.0) ? d : 1.0;
    v.z = sqrtf(1.001 - d*d);
    glm::normalize(v);
    return v;
}
