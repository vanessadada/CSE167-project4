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

int isW;
int isS = 1;
int isA;
int isD;

int isFront;
int isLeft;
int isBack;
int isRight;
int isLeftD;
int isRightD;

float isStop = 0.0;

float deltaTime = 0.0f;    // time between current frame and last frame
float lastFrame = 0.0f;

float stopTime1 = 12 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/20-12));
float stopTime2 = 20 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(25-20)));

float stopTime3 = 11 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/25-11));
float stopTime4 = 25 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(30-25)));

float stopTime5 = 13 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/20-13));
float stopTime6 = 20 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(27-20)));

float stopTime7 = 10 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/25-10));
float stopTime8 = 25 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(32-25)));

float disappearTime1 = 40 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/50-40));
float disappearTime2 = 45 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/55-45));
float disappearTime3 = 35 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/45-35));
float disappearTime4 = 40 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/47-40));

float appearTime1 = 5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/9-5));
float appearTime2 = 4 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/9-4));
float appearTime3 = 6 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/11-6));
float appearTime4 = 5 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/8-5));

// Objects to Render
Cube * Window::cube;
PointCloud * Window::cubePoints;
skyBox * Window::skybox;
Sphere * Window::sphere;
Transform * Window::cone;
Transform * Window::cylinder1;
Transform * Window::teapot1;
Transform * Window::teapot2;
Geometry * Window::coneModel;
Geometry * Window::cy1model;
Geometry * Window::te1model;
Geometry * Window::te2model;

Geometry * Window::lobby;
Geometry * Window::astroStand;
Geometry * Window::astroStand1;
Geometry * Window::astroStand2;
Geometry * Window::astroStand3;
Geometry * Window::astroStand4;


Transform * Window::lobbyRoot;
Transform * Window::astroStandChild;
Transform * Window::astroStand1Child;
Transform * Window::astroStand2Child;
Transform * Window::astroStand3Child;
Transform * Window::astroStand4Child;

BoundingSphere * Window::box1;
BoundingSphere * Window::box2;
BoundingSphere * Window::a;
BoundingSphere * Window::a1;
BoundingSphere * Window::a2;
BoundingSphere * Window::a3;
BoundingSphere * Window::a4;
BoundingSphere * Window::frontWall;
BoundingSphere * Window::backStair;
BoundingSphere * Window::leftWall;
BoundingSphere * Window::rightWall;
BoundingSphere * Window::leftDiag;
BoundingSphere * Window::rightDiag;

ParticleSystem * Window::partAppear;
ParticleSystem * Window::partAppear1;
ParticleSystem * Window::partAppear2;
ParticleSystem * Window::partAppear3;

ParticleSystem * Window::partDis;
ParticleSystem * Window::partDis1;
ParticleSystem * Window::partDis2;
ParticleSystem * Window::partDis3;

Geometry * Window::astroMove1;
Geometry * Window::astroMove2;
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
GLuint Window::toonShader;
GLuint Window::particleShader;



bool Window::initializeProgram() {
	// Create a shader program with a vertex shader and a fragment shader.
	shaderProgram = LoadShaders("shaders/shader.vert", "shaders/shader.frag");
    sphereShader = LoadShaders("shaders/sphereShader.vert", "shaders/sphereShader.frag");
    modelShader = LoadShaders("shaders/modelShader.vert", "shaders/modelShader.frag");
    toonShader = LoadShaders("shaders/ToonShader.vert", "shaders/ToonShader.frag");
    particleShader = LoadShaders("shaders/ParticleShader.vert", "shaders/ParticleShader.frag");
    
	// Check the shader program.
	if (!shaderProgram || !sphereShader || ! modelShader || !toonShader || !particleShader)
	{
		std::cerr << "Failed to initialize shader program" << std::endl;
		return false;
	}

	return true;
}

bool Window::initializeObjects()
{
    //color position size isCylinder degree
    lobbyRoot = new Transform(glm::mat4(1));
    lobby = new Geometry("shaders/amongus_lobby.obj", glm::vec3(0.7529,0.7529,0.7529), glm::vec3(0), glm::vec3(1), 1, 0);
    lobbyRoot->matrixM = lobbyRoot->matrixM * glm::scale(glm::mat4(1), glm::vec3(1.35));
    lobbyRoot->matrixM = lobbyRoot->matrixM * glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(1,0,0));
//    lobbyRoot->matrixM = lobbyRoot->matrixM * glm::translate(glm::mat4(1),glm::vec3(0,-12,-10));
    lobby->setView(view);
    lobby->setShader(modelShader);
    lobby->setProjection(projection);
    lobbyRoot->addChild(lobby);
    
    //black
    astroStandChild = new Transform(glm::mat4(1));
    astroStand = new Geometry("shaders/amongus_astro_still.obj", glm::vec3(0.2431,0.2784,0.3058), glm::vec3(-5,0,3), glm::vec3(0.15), 1, 0);
    astroStandChild->matrixM = astroStandChild->matrixM * glm::scale(glm::mat4(1), glm::vec3(0.05));
    astroStandChild->matrixM = astroStandChild->matrixM * glm::translate(glm::mat4(1), glm::vec3(20,-35,15));
//    astroStandChild->matrixM = astroStandChild->matrixM * glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(1,0,0));
    astroStand->setView(view);
    astroStand->setShader(toonShader);
    astroStand->setProjection(projection);
    astroStandChild->addChild(astroStand);
    lobbyRoot->addChild(astroStandChild);
    
    //blue
    astroStand1Child = new Transform(glm::mat4(1));
    astroStand1 = new Geometry("shaders/amongus_astro_still.obj", glm::vec3(0.075,0.18,0.82), glm::vec3(5,0,3), glm::vec3(0.05), 1, 0);
    float r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    astroStand1Child->matrixM = astroStand1Child->matrixM * glm::scale(glm::mat4(1), glm::vec3(0.05));
    astroStand1Child->matrixM = astroStand1Child->matrixM * glm::translate(glm::mat4(1), (glm::vec3(110 * r1,-35,100)));
    float ro1 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/360.0));
    astroStand1Child->matrixM = astroStand1Child->matrixM * glm::rotate(glm::mat4(1), glm::radians(ro1), glm::vec3(0,1,0));
    astroStand1->setView(view);
    astroStand1->setShader(toonShader);
    astroStand1->setProjection(projection);
    astroStand1Child->addChild(astroStand1);
    lobbyRoot->addChild(astroStand1Child);
    
    //brown
    astroStand2Child = new Transform(glm::mat4(1));
    astroStand2 = new Geometry("shaders/amongus_astro_still.obj", glm::vec3(0.443,0.286,0.114), glm::vec3(3,0,3), glm::vec3(0.05), 1, 0);
    float r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    astroStand2Child->matrixM = astroStand2Child->matrixM * glm::scale(glm::mat4(1), glm::vec3(0.05));
    astroStand2Child->matrixM = astroStand2Child->matrixM * glm::translate(glm::mat4(1), glm::vec3(-80 * r2,-35,60));
    float ro2 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/360.0));
    astroStand2Child->matrixM = astroStand2Child->matrixM * glm::rotate(glm::mat4(1), glm::radians(ro2), glm::vec3(0,1,0));
    astroStand2->setView(view);
    astroStand2->setShader(toonShader);
    astroStand2->setProjection(projection);
    astroStand2Child->addChild(astroStand2);
    lobbyRoot->addChild(astroStand2Child);
    
    //cyan
    astroStand3Child = new Transform(glm::mat4(1));
    astroStand3 = new Geometry("shaders/amongus_astro_still.obj", glm::vec3(0.224,0.996,0.867), glm::vec3(1,0,3), glm::vec3(0.05), 1, 0);
    float r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    astroStand3Child->matrixM = astroStand3Child->matrixM * glm::scale(glm::mat4(1), glm::vec3(0.05));
    astroStand3Child->matrixM = astroStand3Child->matrixM * glm::translate(glm::mat4(1), glm::vec3(100*r3,-35,100));
    float ro3 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/360.0));
    astroStand3Child->matrixM = astroStand3Child->matrixM * glm::rotate(glm::mat4(1), glm::radians(ro3), glm::vec3(0,1,0));
    astroStand3->setView(view);
    astroStand3->setShader(toonShader);
    astroStand3->setProjection(projection);
    astroStand3Child->addChild(astroStand3);
    lobbyRoot->addChild(astroStand3Child);
    
    //dark green
    astroStand4Child = new Transform(glm::mat4(1));
    astroStand4 = new Geometry("shaders/amongus_astro_still.obj", glm::vec3(0.075,0.502,0.173), glm::vec3(7,0,1), glm::vec3(0.05), 1, 0);
    float r4 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
    astroStand4Child->matrixM = astroStand4Child->matrixM * glm::scale(glm::mat4(1), glm::vec3(0.05));
    astroStand4Child->matrixM = astroStand4Child->matrixM * glm::translate(glm::mat4(1), glm::vec3(-70*r4,-35,10));
    float ro4 = static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/360.0));
    astroStand4Child->matrixM = astroStand4Child->matrixM * glm::rotate(glm::mat4(1), glm::radians(ro4), glm::vec3(0,1,0));
    astroStand4->setView(view);
    astroStand4->setShader(toonShader);
    astroStand4->setProjection(projection);
    astroStand4Child->addChild(astroStand4);
    lobbyRoot->addChild(astroStand4Child);
    
    box1 = new BoundingSphere();
    box1->center = glm::vec3(-3,-1.5,2.5);
    box1->radius = 1;
    
    box2 = new BoundingSphere();
    box2->center = glm::vec3(4,-1.5,1.5);
    box2->radius = 1;
    
    frontWall = new BoundingSphere();
    frontWall->normalV = glm::vec3(0,0,-1);
    frontWall->dist = dot(glm::vec3(3,-1.5,6.25), frontWall->normalV);
    
    backStair = new BoundingSphere();
    backStair->normalV = glm::vec3(0,0,1);
    backStair->dist = dot(glm::vec3(3,-1.5,0), backStair->normalV);
    
    leftWall = new BoundingSphere();
    leftWall->normalV = glm::vec3(1,0,0);
    leftWall->dist = dot(glm::vec3(-6,-1.5,1), leftWall->normalV);
    
    rightWall = new BoundingSphere();
    rightWall->normalV = glm::vec3(-1,0,0);
    rightWall->dist = dot(glm::vec3(6.5,-1.5,1), rightWall->normalV);
    
    leftDiag = new BoundingSphere();
    leftDiag->normalV = glm::normalize(leftWall->normalV+frontWall->normalV);
    leftDiag->dist = dot(glm::vec3(-5.5,-1.5,5), leftDiag->normalV);
    
    rightDiag = new BoundingSphere();
    rightDiag->normalV = glm::normalize(frontWall->normalV+rightWall->normalV);
    rightDiag->dist = dot(glm::vec3(5.5,-1.5,5.5), rightDiag->normalV);
    
    a = new BoundingSphere();
    a1 = new BoundingSphere();
    a1->mod = astroStand1Child;
    a2 = new BoundingSphere();
    a2->mod = astroStand2Child;
    a3 = new BoundingSphere();
    a3->mod = astroStand3Child;
    a4 = new BoundingSphere();
    a4->mod = astroStand4Child;
    
    a1->setDirt(astroStand1Child->matrixM[3]);
    a2->setDirt(astroStand2Child->matrixM[3]);
    a3->setDirt(astroStand3Child->matrixM[3]);
    a4->setDirt(astroStand4Child->matrixM[3]);
    
    a->addSphere(box1);
    a->addSphere(box2);
    a->addSphere(a1);
    a->addSphere(a2);
    a->addSphere(a3);
    a->addSphere(a4);
    a->addWall(frontWall);
    a->addWall(backStair);
    a->addWall(leftDiag);
    a->addWall(rightDiag);
    a->addWall(leftWall);
    a->addWall(rightWall);
    
//    a1->addSphere(box1);
//    a1->addSphere(box2);
    a1->addSphere(a);
    a1->addSphere(a2);
    a1->addSphere(a3);
    a1->addSphere(a4);
    a1->addWall(frontWall);
    a1->addWall(backStair);
    a1->addWall(leftDiag);
    a1->addWall(rightDiag);
    a1->addWall(leftWall);
    a1->addWall(rightWall);
    
//    a2->addSphere(box1);
//    a2->addSphere(box2);
    a2->addSphere(a1);
    a2->addSphere(a);
    a2->addSphere(a3);
    a2->addSphere(a4);
    a2->addWall(frontWall);
    a2->addWall(backStair);
    a2->addWall(leftDiag);
    a2->addWall(rightDiag);
    a2->addWall(leftWall);
    a2->addWall(rightWall);
    
//    a3->addSphere(box1);
//    a3->addSphere(box2);
    a3->addSphere(a1);
    a3->addSphere(a2);
    a3->addSphere(a);
    a3->addSphere(a4);
    a3->addWall(frontWall);
    a3->addWall(backStair);
    a3->addWall(leftDiag);
    a3->addWall(rightDiag);
    a3->addWall(leftWall);
    a3->addWall(rightWall);
    
//    a4->addSphere(box1);
//    a4->addSphere(box2);
    a4->addSphere(a1);
    a4->addSphere(a2);
    a4->addSphere(a3);
    a4->addSphere(a);
    a4->addWall(frontWall);
    a4->addWall(backStair);
    a4->addWall(leftDiag);
    a4->addWall(rightDiag);
    a4->addWall(leftWall);
    a4->addWall(rightWall);
    
    a->createBounding(astroStandChild->matrixM);
    a1->createBounding(astroStand1Child->matrixM);
    a2->createBounding(astroStand2Child->matrixM);
    a3->createBounding(astroStand3Child->matrixM);
    a4->createBounding(astroStand4Child->matrixM);

    partAppear = new ParticleSystem(a1);
    partAppear1 = new ParticleSystem(a2);
    partAppear2 = new ParticleSystem(a3);
    partAppear3 = new ParticleSystem(a4);
    
    partDis = new ParticleSystem(a1);
    partDis1 = new ParticleSystem(a2);
    partDis2 = new ParticleSystem(a3);
    partDis3 = new ParticleSystem(a4);
    
//    astroStand1->isRender = 0;
//    astroStand2->isRender = 0;
//    astroStand3->isRender = 0;
//    astroStand4->isRender = 0;
    
    astroMove1 = new Geometry("shaders/amongus_astro_moving1.obj", glm::vec3(1,0,0), glm::vec3(0), glm::vec3(1), 1, 0);
    astroMove1->setView(view);
    astroMove1->setShader(modelShader);
    astroMove1->setProjection(projection);
    
    astroMove2 = new Geometry("shaders/amongus_astro_moving2.obj", glm::vec3(1,0,0), glm::vec3(0), glm::vec3(1), 1, 0);
    astroMove2->setView(view);
    astroMove2->setShader(modelShader);
    astroMove2->setProjection(projection);
    

	return true;
}

void Window::cleanUp()
{
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
    a->createBounding(astroStandChild->matrixM);
    a1->createBounding(astroStand1Child->matrixM);
    a2->createBounding(astroStand2Child->matrixM);
    a3->createBounding(astroStand3Child->matrixM);
    a4->createBounding(astroStand4Child->matrixM);
    
    astroStand1->isRender = 0;
    astroStand2->isRender = 0;
    astroStand3->isRender = 0;
    astroStand4->isRender = 0;
    
    if(lastFrame > appearTime1){
        partAppear->isBegin = 1;
        if(partAppear->intensity > 1){
               partAppear->isDone = 1;
               partAppear->isBegin = 0;
           }
           partAppear->update(deltaTime, a1, 2);
           partAppear->intensity += 0.001;
        if(partAppear->isDone == 1){
            astroStand1->isRender = 1;
            a1->isRender = 1;
        }
    }

    if(lastFrame > appearTime2){
        partAppear1->isBegin = 1;
        if(partAppear1->intensity >1){
            partAppear1->isDone = 1;
            partAppear1->isBegin = 0;
        }
        partAppear1->update(deltaTime, a2, 2);
        partAppear1->intensity += 0.001;
        if(partAppear1->isDone == 1){
            astroStand2->isRender = 1;
            a2->isRender = 1;
        }
    }
    
    if(lastFrame > appearTime3){
        partAppear2->isBegin = 1;
        if(partAppear2->intensity >1){
            partAppear2->isDone = 1;
            partAppear2->isBegin = 0;
        }
        partAppear2->update(deltaTime, a3, 2);
        partAppear2->intensity += 0.001;
        if(partAppear2->isDone == 1){
            astroStand3->isRender = 1;
            a3->isRender = 1;
        }
    }
    
    if(lastFrame > appearTime4){
        partAppear3->isBegin = 1;
        if(partAppear3->intensity > 1){
            partAppear3->isDone = 1;
            partAppear3->isBegin = 0;
        }
        partAppear3->update(deltaTime, a4, 2);
        partAppear3->intensity += 0.001;
        if(partAppear3->isDone == 1){
            astroStand4->isRender = 1;
            a4->isRender = 1;
        }
    }

    
    if(lastFrame > disappearTime1){
        partDis->isBegin = 1;
        if(partDis->intensity > 1){
            partDis->isDisDone = 1;
            partDis->isBegin = 0;
        }
        partDis->intensity += 0.001;
        partDis->updateDis(deltaTime, a1, 2);
        if(partDis->isDisDone == 1){
            astroStand1->isRender = 0;
            a1->isRender = 0;
        }
    }
    
    if(lastFrame > disappearTime2){
        partDis1->isBegin = 1;
        if(partDis1->intensity > 1){
            partDis1->isDisDone = 1;
            partDis1->isBegin = 0;
        }
        partDis1->intensity += 0.001;
        partDis1->updateDis(deltaTime, a2, 2);
        if(partDis1->isDisDone == 1){
            astroStand2->isRender = 0;
            a2->isRender = 0;
        }
    }
    
    if(lastFrame > disappearTime3){
        partDis2->isBegin = 1;
        if(partDis2->intensity > 1){
            partDis2->isDisDone = 1;
            partDis2->isBegin = 0;
        }
        partDis2->intensity += 0.001;
        partDis2->updateDis(deltaTime, a3, 2);
        if(partDis2->isDisDone == 1){
            astroStand3->isRender = 0;
            a3->isRender = 0;
        }
    }
    
    if(lastFrame > disappearTime4){
        partDis3->isBegin = 1;
        if(partDis3->intensity > 1){
            partDis3->isDisDone = 1;
            partDis3->isBegin = 0;
        }
        partDis3->intensity += 0.001;
        partDis3->updateDis(deltaTime, a4, 2);
        if(partDis3->isDisDone == 1){
            astroStand4->isRender = 0;
            a4->isRender = 0;
        }
    }

    
    isFront = 0;
    isRightD = 0;
    isLeftD = 0;
    isBack = 0;
    isLeft = 0;
    isRight = 0;
    
    if(partAppear->isDone == 1){
        if(stopTime1 > lastFrame || lastFrame > stopTime2){
            move(astroStand1Child, a1);
        }
    }
    if(partAppear1->isDone == 1){
        if(stopTime3 > lastFrame || lastFrame > stopTime4){
            move(astroStand2Child, a2);
        }
    }
    
    if(partAppear2->isDone == 1){
        if(stopTime5 > lastFrame || lastFrame > stopTime6){
            move(astroStand3Child, a3);
        }
    }

    if(partAppear3->isDone == 1){
        if(stopTime7 > lastFrame || lastFrame > stopTime8){
            move(astroStand4Child, a4);
        }
    }
    
    if (a->checkCollisionWall(a, frontWall))
        {
            isFront = 1;
        }
    if (a->checkCollisionWall(a, leftWall))
        {
            isLeft = 1;
        }
    if(a->checkCollisionWall(a, rightWall))
        {
            isRight = 1;
        }
    if(a->checkCollisionWall(a, backStair))
        {
            isBack = 1;
        }
    if(a->checkCollisionWall(a, leftDiag))
        {
            isLeftD = 1;
        }
    if(a->checkCollisionWall(a, rightDiag))
        {
            isRightD = 1;
        }
    for (auto& ball : a->allBoundingsphere)
        {
            if(a->checkCollisionSphere(a, ball))
                {
                    if (a->direction == glm::vec3(0,0,1))
                        {
                            isFront = 1;
                        }
                    if (a->direction == glm::vec3(0,0,-1))
                        {
                            isBack = 1;
                        }
                    if(a->direction == glm::vec3(1,0,0))
                        {
                            isRight = 1;
                        }
                    if(a->direction == glm::vec3(-1,0,0))
                        {
                            isLeft = 1;
                        }
                }
        }
}

void Window::displayCallback(GLFWwindow* window)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    lobbyRoot->draw(glm::mat4(1));
//    astroStandChild->draw(glm::mat4(1));
    
    if(partAppear->isBegin == 1){
        partAppear->draw(particleShader, view, projection, a1->center);
    }
    if(partAppear1->isBegin == 1){
//        partAppear1->model = partAppear1->model * glm::translate(glm::mat4(1), a2->center);
        partAppear1->draw(particleShader, view, projection, a2->center);
    }
    if(partAppear2->isBegin == 1){
        partAppear2->draw(particleShader, view, projection, a3->center);
    }
    if(partAppear3->isBegin == 1){
        partAppear3->draw(particleShader, view, projection, a4->center);
    }
    
    if(partDis->isBegin == 1){
        partDis->draw(particleShader, view, projection, a1->center);
    }
    
    if(partDis1->isBegin == 1){
//        partDis1->model = glm::translate(glm::mat4(1), a2->center) * partDis1->model;
//        partDis1->model = glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(1,0,0)) * partDis1->model;
        partDis1->draw(particleShader, view, projection, a2->center);
    }
    
    if(partDis2->isBegin == 1){
//        partDis2->model = glm::translate(glm::mat4(1), a3->center) * partDis2->model;
//        partDis2->model = glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(1,0,0)) * partDis2->model;
        partDis2->draw(particleShader, view, projection, a3->center);
    }
    
    if(partDis3->isBegin == 1){
//        partDis3->model = glm::translate(glm::mat4(1), a4->center) * partDis3->model;
//        partDis3->model = glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(1,0,0)) * partDis3->model;
        partDis3->draw(particleShader, view, projection, a4->center);
    }
    
    
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
        float cameraSpeed = 0.1;
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);				
			break;
                
        //move back
		case GLFW_KEY_1:
                eyePos += cameraSpeed * eyePos;
                //1eyePos = glm::vec3(0,0,10);
			break;
        //move forward
		case GLFW_KEY_2:
                eyePos -= cameraSpeed * eyePos;
                
			break;
        //back to origin
        case GLFW_KEY_3:
                eyePos = glm::vec3(0,0,20);
                lookAtPoint = glm::vec3(0,0,0);
            
            break;
        //move north
        case GLFW_KEY_W:
                if (isBack == 0){
                    if (isA == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0,1,0));
                    }
                    if (isD == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0,1,0));
                    }
                    if (isS == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0,1,0));
                    }
                    astroStandChild->matrixM *= glm::translate(glm::mat4(1), glm::vec3(0,0,5));
                    isS = 0;
                    isA = 0;
                    isD = 0;
                    isW = 1;
                    a->direction = glm::vec3(0,0,-1);
               }
            break;
                
        //move south
        case GLFW_KEY_S:
                if(isFront == 0 && isRightD == 0 && isLeftD == 0){
                    if (isA == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0,1,0));
                    }
                    if (isD == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0,1,0));
                    }
                    if (isW == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0,1,0));
                    }
                    astroStandChild->matrixM *= glm::translate(glm::mat4(1), glm::vec3(0,0,5));
                    isS = 1;
                    isA = 0;
                    isD = 0;
                    isW = 0;
                    a->direction = glm::vec3(0,0,1);
                }
            break;
                
        //move left
        case GLFW_KEY_A:
                if (isLeft == 0 && isLeftD == 0){
                    if (isW == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0,1,0));
                    }
                    if (isD == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0,1,0));
                    }
                    if (isS == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0,1,0));
                    }
                    astroStandChild->matrixM *= glm::translate(glm::mat4(1), glm::vec3(0,0,5));
                    isA = 1;
                    isS = 0;
                    isD = 0;
                    isW = 0;
                    a->direction = glm::vec3(-1,0,0);
                }
            break;
        //move right
        case GLFW_KEY_D:
                if (isRight == 0 && isRightD == 0){
                    if (isA == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(180.0f), glm::vec3(0,1,0));
                    }
                    if (isW == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(-90.0f), glm::vec3(0,1,0));
                    }
                    if (isS == 1)
                    {
                        astroStandChild->matrixM *= glm::rotate(glm::mat4(1), glm::radians(90.0f), glm::vec3(0,1,0));
                    }
                    astroStandChild->matrixM *= glm::translate(glm::mat4(1), glm::vec3(0,0,5));
                    isS = 0;
                    isA = 0;
                    isD = 1;
                    isW = 0;
                    a->direction = glm::vec3(1,0,0);
                }
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
        lobby->setView(view);
        astroStand->setView(view);
        astroStand1->setView(view);
        astroStand2->setView(view);
        astroStand3->setView(view);
        astroStand4->setView(view);
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
//            direction = lastpoint - curPoint;
        direction = curPoint - lastpoint;
            float velocity = direction.length();
            
            if(velocity > 1){
                glm::vec3 rotAxis;
//                rotAxis = glm::cross(curPoint, lastpoint);
                rotAxis = glm::cross(lastpoint, curPoint);
                rot_angle = velocity * m_ROTSCALE;
                
//              lobbyRoot->matrixM = glm::rotate(glm::mat4(1), rot_angle, rotAxis)* lobbyRoot->matrixM;
                
                   glm::vec3 origin = glm::vec3(0,0,0);
                    glm::mat4 translate = glm::translate(glm::mat4(1), origin);
                    eyePos = glm::vec3(translate * glm::rotate(glm::mat4(1), rot_angle, rotAxis) * inverse(translate) * glm::vec4(eyePos,1));
    
            view = glm::lookAt(Window::eyePos, Window::lookAtPoint, Window::upVector);
                lobby->setView(view);
                astroStand->setView(view);
                astroStand1->setView(view);
                astroStand2->setView(view);
                astroStand3->setView(view);
                astroStand4->setView(view);
        }
        lastpoint = curPoint;
    }
}

void Window::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
//    yoffset = 1 + yoffset;
//    lobbyRoot->scale(yoffset);
//    sphere->model = glm::scale(glm::mat4(1), glm::vec3(yoffset)) * sphere->model;
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

void Window::move(Transform* astro, BoundingSphere*a)
{
    int indicator = 0;
    
    glm::vec3 newDirt;
    float deg;
    
    if (a->checkCollisionWall(a, frontWall)){
        newDirt = glm::reflect(a->direction, frontWall->normalV);
        deg = glm::acos(dot(frontWall->normalV, newDirt)/(length(frontWall->normalV)*length(newDirt)));
//        deg = glm::acos(dot(frontWall->normalV, a->direction)/(length(frontWall->normalV)*length(a->direction)));
        indicator = 1;
    }
    if (a->checkCollisionWall(a, backStair)){
        newDirt = glm::reflect(a->direction, backStair->normalV);
        deg = glm::acos(dot(backStair->normalV, newDirt)/(length(backStair->normalV)*length(newDirt)));
        indicator = 1;
    }
    if (a->checkCollisionWall(a, rightWall)){
        newDirt = glm::reflect(a->direction, rightWall->normalV);
        deg = glm::acos(dot(rightWall->normalV, newDirt)/(length(rightWall->normalV)*length(newDirt)));
        indicator = 1;
    }
    if (a->checkCollisionWall(a, leftWall)){
        newDirt = glm::reflect(a->direction, leftWall->normalV);
        deg = glm::acos(dot(leftWall->normalV, newDirt)/(length(leftWall->normalV)*length(newDirt)));
        indicator = 1;
    }
    if (a->checkCollisionWall(a, leftDiag)){
        newDirt = glm::reflect(a->direction, leftDiag->normalV);
        deg = glm::acos(dot(leftDiag->normalV, newDirt)/(length(leftDiag->normalV)*length(newDirt)));
        indicator = 1;
    }
    if (a->checkCollisionWall(a, rightDiag)){
        newDirt = glm::reflect(a->direction, rightDiag->normalV);
        deg = glm::acos(dot(rightDiag->normalV, newDirt)/(length(rightDiag->normalV)*length(newDirt)));
        indicator = 1;
    }
    
    if(indicator == 1){
            astro->matrixM = astro->matrixM * glm::rotate(glm::mat4(1),glm::degrees(2*(90.0f-deg)), glm::vec3(0,1,0));
        }
    
    if(indicator == 0){
    //only other astronauts
        int isBall = 0;
        for (auto& ball: a->allBoundingsphere){
            if (ball->isRender != 0){
                if (a->checkCollisionSphere(a, ball)){
                    glm::vec3 nor = a->center - ball->center;
                    newDirt = glm::reflect(a->direction, nor);
                    float deg = glm::acos(dot(-nor, newDirt)/(length(nor)*length(newDirt)));
                    astro->matrixM = astro->matrixM * glm::rotate(glm::mat4(1), deg, glm::vec3(0,1,0));
                    isBall = 1;
                }
            }
        }
        
        if(isBall != 1){
            //check two box
            if(a->checkCollisionSphere(a, box1)){
                glm::vec3 nor = a->center - box1->center;
                newDirt = glm::reflect(a->direction, nor);
                float deg = glm::acos(dot(-nor, newDirt)/(length(nor)*length(newDirt)));
                astro->matrixM = astro->matrixM * glm::rotate(glm::mat4(1), deg, glm::vec3(0,1,0));
            }
            
            if(a->checkCollisionSphere(a, box2)){
                glm::vec3 nor = a->center - box2->center;
                newDirt = glm::reflect(a->direction, nor);
                float deg = glm::acos(dot(-nor, newDirt)/(length(nor)*length(newDirt)));
                astro->matrixM = astro->matrixM * glm::rotate(glm::mat4(1), deg, glm::vec3(0,1,0));
            }
        }
    }
    
    astro->matrixM = astro->matrixM * glm::translate(glm::mat4(1), glm::vec3(0,0,0.1));
//    astro->matrixM = astro->matrixM * glm::rotate(glm::mat4(1), glm::radians(0.01f), glm::vec3(0,1,0));
}


