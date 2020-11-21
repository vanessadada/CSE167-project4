#include "Window.h"

// Window Properties
int Window::width;
int Window::height;
const char* Window::windowTitle = "GLFW Starter Project";
const double m_ROTSCALE = 90.0;
bool but = false;
bool firstmouse = true;
int isForward = 0;
int isAround = 0;
int isUpdown = 0;
int isSpin = 0;

float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

// Objects to Render
Cube * Window::cube;
PointCloud * Window::cubePoints;
skyBox * Window::skybox;
Sphere * Window::sphere;
Transform * Window::cone;
Transform * Window::cylinder1;
Transform * Window::cylinder2;
Transform * Window::cylinder3;
Transform * Window::cylinder4;
Transform * Window::cylinder5;
Transform * Window::cylinder6;
Transform * Window::teapot1;
Transform * Window::teapot2;
Transform * Window::teapot3;
Transform * Window::teapot4;
Transform * Window::teapot5;
Transform * Window::teapot6;
Geometry * Window::coneModel;
Geometry * Window::cy1model;
Geometry * Window::te1model;
Geometry * Window::te2model;
//Object* currObj;
PointCloud * currObj;


glm::vec3 Window::lastpoint(0,0,0);

// Camera Matrices 
// Projection matrix:
glm::mat4 Window::projection; 

// View Matrix:
glm::vec3 Window::eyePos(0, 0, 20);			// Camera position.
glm::vec3 Window::lookAtPoint(0, 0, 0);		// The point we are looking at.
glm::vec3 Window::upVector(0, 1, 0);		// The up direction of the camera.
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::mat4 Window::view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);

float lastX = Window::width/2;
float lastY = Window::height/2;


// Shader Program ID
GLuint Window::shaderProgram;
GLuint Window::sphereShader;
GLuint Window::modelShader;



bool Window::initializeProgram() {
	// Create a shader program with a vertex shader and a fragment shader.
	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    sphereShader = LoadShaders("shaders/sphereShader.vert", "shaders/sphereShader.frag");
    modelShader = LoadShaders("shaders/modelShader.vert", "shaders/modelShader.frag");
    
    
	// Check the shader program.
	if (!shaderProgram || !sphereShader || ! modelShader)
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
 
	// Setcube to be the first to display
	//currObj = cube;
    skybox = new skyBox("right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg");
    sphere = new Sphere();
    cube = new Cube(16);
    
    cone = new Transform(glm::mat4(1));
    coneModel = new Geometry("cone.obj", glm::vec3(1,0,0), glm::vec3(0,-10,-10), glm::vec3(1),1, 0);
    coneModel->setView(view);
    coneModel->setShader(modelShader);
    coneModel->setProjection(projection);
    cone->addChild(coneModel);
    
    
    cylinder1 = new Transform(glm::mat4(1));
    //color position size isCylinder degree
    cy1model = new Geometry("torus_lr.obj", glm::vec3(0,1,0), glm::vec3(0, -10, -10), glm::vec3(0.75),0, 0);
    cy1model->setView(view);
    cy1model->setShader(modelShader);
    cy1model->setProjection(projection);
    cylinder1->addChild(cy1model);
    cone->addChild(cylinder1);
    
    
    teapot1 = new Transform(glm::mat4(1));
    te1model = new Geometry("teapot.obj", glm::vec3(0,0,1), glm::vec3(-24,-40,-40), glm::vec3(0.15),0, 0);
    te1model->setView(view);
    te1model->setShader(modelShader);
    te1model->setProjection(projection);
    teapot1->addChild(te1model);
    cylinder1->addChild(teapot1);
    
    /*
    teapot2 = new Transform(glm::mat4(1));
    te2model = new Geometry("shaders/teapot.obj", glm::vec3(1,1,0), glm::vec3(15,7,6), glm::vec3(0.15), 0, -100);
    te2model->setView(view);
    te2model->setShader(modelShader);
    te2model->setProjection(projection);
    teapot2->addChild(te2model);
    cylinder1->addChild(teapot2);*/
	return true;
}

void Window::cleanUp()
{
	// Deallcoate the objects.
	//delete cube;
	//delete cubePoints;
    
	// Delete the shader program.
	glDeleteProgram(shaderProgram);
    glDeleteProgram(sphereShader);
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
	//skybox->update();
    sphere->update();
    
    cone->update(0,0,isUpdown);
    //cylinder1->update(0,0, isUpdown);
    teapot1->update(isSpin,isAround, isUpdown);
    //cy1model->update(1,0);
    //teapot2->update(1,1);
    //coneModel->update();
    //te1model->update();
    
}

void Window::displayCallback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
	// Render the objects
    //view = glm::mat4(glm::mat3(view));
    skybox->draw(view, projection, shaderProgram);
    
    sphere->setEye(eyePos);
    sphere->draw(view, projection, sphereShader);
    cube->draw(view, projection, modelShader);
    
    cone->draw(glm::mat4(1));
    //currObj->draw(view, projection, modelShader);
    
    

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
        float cameraSpeed = 2.5;
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);				
			break;
                
        //move forward
		case GLFW_KEY_1:
                eyePos += cameraSpeed * cameraFront;
                //1eyePos = glm::vec3(0,0,10);
			break;
        //move back
		case GLFW_KEY_2:
                eyePos -= cameraSpeed * cameraFront;
                
			break;
        //back to origin
        case GLFW_KEY_3:
                eyePos = glm::vec3(0,0,20);
                lookAtPoint = glm::vec3(0,0,0);
            
            break;
        //move up
        case GLFW_KEY_W:
                eyePos += cameraSpeed * upVector;
                //eyePos = glm::vec3(0,10,20);
                
            break;
        //move down
        case GLFW_KEY_S:
                eyePos -= cameraSpeed * upVector;
                //eyePos = glm::vec3(0,-20,20);
                
            break;
        //move left
        case GLFW_KEY_A:
                eyePos -= glm::normalize(glm::cross(cameraFront, upVector)) * cameraSpeed;
                
                //lookAtPoint = glm::vec3(20,0,20);
                //eyePos = glm::vec3(20,-20,50);
            break;
        //move right
        case GLFW_KEY_D:
                eyePos += glm::normalize(glm::cross(cameraFront, upVector)) * cameraSpeed;
                //lookAtPoint = glm::vec3(-20,0,20);
                
            break;
        case GLFW_KEY_4:
                if (isUpdown == 0)
                    isUpdown = 1;
                else
                    isUpdown = 0;
                break;
            case GLFW_KEY_5:
                if (isAround == 0)
                    isAround = 1;
                else
                    isAround = 0;
                break;
            case GLFW_KEY_6:
                if (isSpin == 0)
                    isSpin = 1;
                else
                    isSpin = 0;
                break;
		default:
			break;
		}
        
        view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
        cy1model->setView(view);
        coneModel->setView(view);
        te1model->setView(view);
        //te2model->setView(view);
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
            direction = lastpoint - curPoint;
            float velocity = direction.length();
            
            if(velocity > 1){
                glm::vec3 rotAxis;
                rotAxis = glm::cross(curPoint, lastpoint);
                rot_angle = velocity * m_ROTSCALE;
                
            
                    glm::vec3 origin = eyePos;
                    glm::mat4 translate = glm::translate(glm::mat4(1), origin);
                    lookAtPoint = glm::vec3(translate * glm::rotate(glm::mat4(1), rot_angle, rotAxis) * inverse(translate) * glm::vec4(lookAtPoint,1));
    
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                cy1model->setView(view);
                coneModel->setView(view);
                te1model->setView(view);
        }
    }
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    /*
    glm::vec3 origin = glm::vec3(0,0,0);
    glm::mat4 translate = glm::translate(glm::mat4(1), origin);
    
    eyePos = glm::vec3(translate * glm::scale(glm::vec3(yoffset)) * inverse(translate) * glm::vec4(eyePos,1));
    
     view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
    
    

    if(sOr == 1){
        yoffset = 1 + yoffset;
        //currObj->scale(yoffset);
    }
    else if(sOr == 2){
        yoffset = 1 + yoffset;
        //lightSource->scale(yoffset);
    }
    else{
        yoffset = 1 + yoffset;
        //currObj->scale(yoffset);
        //lightSource->scale(yoffset);
        
    }*/
    
    
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
