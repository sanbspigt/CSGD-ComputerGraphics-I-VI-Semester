#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include<cmath>
#include<ShaderH.h>

void frameBufferSizeCallBack(GLFWwindow* window,int width,int height);
void ProcessInput(GLFWwindow* window);

const unsigned int SCR_WIDTH = 640;
const unsigned int SCR_HEIGHT = 640;

int main()
{
	//GLFW Initilization--------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	//----------------------------------------
	
	//Window Creation------------------
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"MY FIRST WINDOW",NULL,NULL);
	if (window == NULL)
	{
		std::cout<< "FAILED TO CREATE THE WINDOW!!"<<std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);
	//---------------------------------------------
	//GLAD Initialization
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "GLAD is not initialized!!"<<std::endl;
		glfwTerminate();
		return -1;
	}

	Shader TriShader = Shader("vertex.shader","fragment.shader");

	float vertices[] = {
		-0.5f,-0.5f,0.0f,// left - 0th STRIDE
		0.5f,-0.5f,0.0f, //right - 1st STRIDE
		0.0f,0.5f,0.0f // top - 2nd STRIDE
	};

	//VBO - Vertex Buffer Object || VAO - Vertex Array Object
	unsigned int VBO, VAO;

	//VBO Declaration
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//VAO Declaration
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);


	glBindBuffer(GL_ARRAY_BUFFER, 0);// unbinding the current allocated VBO
	glBindVertexArray(0); // unbinding the current allocated VAO
	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Inputs
		ProcessInput(window);

		//float time = sinf(glfwGetTime());

		//Render
		glClearColor(0.6f,0.5f,0.8f,1.0f);//RGBA Color space value
		glClear(GL_COLOR_BUFFER_BIT);

		TriShader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES,0,3);

		//Buffer Swapping And Event Tracking
		glfwSwapBuffers(window);
		glfwPollEvents();

	}

	glfwTerminate();
	return 0;
}

void frameBufferSizeCallBack(GLFWwindow* window, int width, int height)
{
	glViewport(0,0,width,height);
}
void ProcessInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}