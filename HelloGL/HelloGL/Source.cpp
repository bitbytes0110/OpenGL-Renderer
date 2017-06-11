#include<glad\glad.h>
#include<GLFW\glfw3.h>

#include<iostream>

#define WIDTH	1280
#define HEIGHT  720


#define DEBUG(printString) std::cout<< printString<< std::endl;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

void processInput(GLFWwindow * window);

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "RockGL", NULL, NULL);
	if(window == NULL)
	{
		DEBUG("GLFW3 Window Inititalization Failed");
		glfwTerminate();
		return -1;
	}
	else
	{
		DEBUG("GLFW3 Window Inititalization SUCCESS !");
	}
	glfwMakeContextCurrent(window);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEBUG("GLAD loading failed");
		return -1;
	}
	glViewport(0,0, WIDTH, HEIGHT);


	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	while (!glfwWindowShouldClose(window))	// Game Loop
	{
		processInput(window);

		// Render
		glClearColor(0.2f,0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window);
		glfwPollEvents();	
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}