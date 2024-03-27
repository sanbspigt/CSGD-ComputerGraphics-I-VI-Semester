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
	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH,SCR_HEIGHT,"SQUARE RENDER",NULL,NULL);
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

	// set up vertex data (and buffer(s)) and configure vertex attributes
  // ------------------------------------------------------------------
	float vertices[] = {
		 0.5f,  0.5f, 0.0f,  // top right
		 0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};
	unsigned int indices[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	//VBO - Vertex Buffer Object || VAO - Vertex Array Object || EBO - Element Buffer Object
	unsigned int VBO, VAO , EBO;

	//VBO Declaration
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//VAO Declaration
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);
	//EBO Declaration
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
		//glDrawArrays(GL_TRIANGLES,0,3); - X
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

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