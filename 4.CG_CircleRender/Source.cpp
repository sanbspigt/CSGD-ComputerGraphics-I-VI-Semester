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

	//------Circle Calculations
	const float radius = 0.6f;
	const int divisions = 300;
	float angle = 0.0f;
	float TotalAngle = 2 * 2 * acos(0.0f);//3.141518......
	float vertices[divisions*6];
	int i = 0;

	while (i < divisions)
	{
		angle = (TotalAngle * float(i)) / (float)divisions;

		float xValue = cos(angle) * radius;
		float yValue = sin(angle) * radius;

		//XYZ Coord values
		vertices[(i * 6)] = xValue;
		vertices[(i * 6)+1] = yValue;
		vertices[(i * 6)+2] = 0.0f;
		//RGB Color values
		vertices[(i * 6)+3] = sinf(xValue);
		vertices[(i * 6)+4] = cosf(yValue);
		vertices[(i * 6)+5] = cosf(yValue);
		std::cout << "Coord: X,Y" << xValue << "," << yValue << std::endl;
		i++;
	}

	//----------------------------

	//VBO - Vertex Buffer Object || VAO - Vertex Array Object
	unsigned int VBO, VAO;

	//VBO Declaration
	glGenBuffers(1,&VBO);
	glBindBuffer(GL_ARRAY_BUFFER,VBO);
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	//VAO Declaration
	glGenVertexArrays(1,&VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,6*sizeof(float),(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3*sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);// unbinding the current allocated VBO
	glBindVertexArray(0); // unbinding the current allocated VAO
	//Render loop
	while (!glfwWindowShouldClose(window))
	{
		//Inputs
		ProcessInput(window);
		//glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		//float time = sinf(glfwGetTime());
		float timeT = glfwGetTime();
		//Render
		glClearColor(0.6f,0.5f,0.8f,1.0f);//RGBA Color space value
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(3.0f);
		TriShader.use();
		TriShader.setFloat("timeT",cosf(timeT));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLE_FAN,0,divisions);
		//glDrawArrays(GL_LINE_LOOP,0,divisions);
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