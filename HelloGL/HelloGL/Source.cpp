#include<glad\glad.h>
#include<GLFW\glfw3.h>

#include"Macros.h"
#include"Shader.h"
#include<iostream>

void SetWireframe(bool bValue);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void SetWireframe(bool bValue);
void processInput(GLFWwindow * window);

int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// glfw window creation
	// --------------------
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "RockGL", NULL, NULL);
	if(window == NULL)
	{
		DEBUG("GLFW3 Window Inititalization FAILED");
		glfwTerminate();
		return -1;
	}
	else
	{
		DEBUG("GLFW3 Window Inititalization SUCCESS!");
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		DEBUG("GLAD loading failed");
		return -1;
	}

	// build and compile our shader program
	// ------------------------------------
	Shader ourShaderProgram("shader.VS", "shader.FS");

	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		// positions         // colors
		0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
	};


	//	Vertex Buffer Object		( Stores all vertex data )
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Setting the vertex attributes (how the vertex data should be interpreted)
	// position attribute
	glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,6*(sizeof(GL_FLOAT)),(void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GL_FLOAT), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);


	// Game Loop
	// ----------------
	while (!glfwWindowShouldClose(window))	
	{
		// Input
		// -----
		processInput(window);

		// Render
		// ------
		glClearColor(0.2f,0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		//	Render the Triangle

		ourShaderProgram.Use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
				
		// End of Rendering Code

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();	
	}


	// De-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void SetWireframe(bool bWireframeMode)
{
	if (bWireframeMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//	Enable
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//	Disable
	}
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, TRUE);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
}