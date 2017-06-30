#include<glad\glad.h>
#include<GLFW\glfw3.h>

#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>

#include<glm\glm.hpp>


#include"stb_image.h"

#include"Macros.h"
#include"Shader.h"
#include<iostream>

int main();

void ConsoleProgramming()
{

	LOG("**----->	Console Programming START	< ----- **\n");
	glm::vec4 InitVec (1.0f, 0.0f, 0.0f, 1.0f);	     
	glm::mat4 transMat;
	transMat = glm::translate(transMat, glm::vec3(1.0f,1.0f,0.0f));
	glm::vec3 finalVec = transMat*InitVec;
	std::cout << finalVec.x << finalVec.y << finalVec.z<<std::endl;

	LOG("**----->	Console Programming END		< ----- **\n");
}

void SetWireframe(bool bValue);

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void SetWireframe(bool bValue);
void processInput(GLFWwindow * window);

float mixValue = 0.4f;

int main()
{

	ConsoleProgramming();
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
		// positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	unsigned int indices[] = {
		0, 1, 2, // first triangle
		0, 2, 3  // second triangle
	};
	//	Vertex Buffer Object		( Stores all vertex data )
	unsigned int VBO, EBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// for indices data 
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Setting the vertex attributes (how the vertex data should be interpreted)
	// position attribute
	glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE, 8*(sizeof(GL_FLOAT)),(void*)0);
	glEnableVertexAttribArray(0);

	// Color attribute
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * (sizeof(GL_FLOAT)), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// Texture attribute
	glVertexAttribPointer(2, 2,GL_FLOAT, GL_FALSE, 8 * (sizeof(GL_FLOAT)), (void*)(6*sizeof(float)));
	glEnableVertexAttribArray(2);
	
	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	// glBindVertexArray(0);

	stbi_set_flip_vertically_on_load(true);	// tell stb_image.h to flip loaded texture's on the y-axis.
	// load and create a texture 
	// -------------------------
	unsigned int myTexture1, myTexture2;

	// TEXTURE 2 
	// ---------

	glGenTextures(1, &myTexture1);
	glBindTexture(GL_TEXTURE_2D, myTexture1);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	// load the image data
	int width, height, nChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nChannels, 0);


	//	Generate texture
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("FAILED TO LOAD TEXTURE");
	}

	stbi_image_free(data);
	
	// TEXTURE 2 
	// ---------

	glGenTextures(1, &myTexture2);
	glBindTexture(GL_TEXTURE_2D, myTexture2);

	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// load the image data

	int width2, height2, nChannels2;
	unsigned char* data2 = stbi_load("face.png", &width2, &height2, &nChannels2, 0);

	//	Generate texture
	if (data2)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width2, height2, 0, GL_RGBA, GL_UNSIGNED_BYTE, data2);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		LOG("FAILED TO LOAD TEXTURE");
	}

	stbi_image_free(data2);
	// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
	// -------------------------------------------------------------------------------------------
	ourShaderProgram.Use();// don't forget to activate/use the shader before setting uniforms!
	ourShaderProgram.SetInt("WoodTexture", 0);
	ourShaderProgram.SetInt("FaceTexture", 1);

	ourShaderProgram.SetFloat("mixValue", mixValue);
	ourShaderProgram.SetFloat("mixValue", mixValue);


	//SetWireframe(TRUE);
	// Game Loop
	// ----------------
	while (!glfwWindowShouldClose(window))	
	{
		// Input
		// -----
		processInput(window);

		// Render
		// ------
		glClearColor(0.05f,0.05f, 0.05f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, myTexture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, myTexture2);

		glm::mat4 trans;
		trans = glm::translate(trans, glm::vec3(0.5f, 0.5f, 0.0f));
		trans = glm::rotate(trans, (float)glfwGetTime(), glm::vec3(0.0f, 0.0f, 1.0f));
		trans = glm::scale(trans, glm::vec3(0.5f, 0.5f, 1.0f));
		
		ourShaderProgram.SetFloat("mixValue", mixValue);
		ourShaderProgram.SetMat4("transMat", trans);

		//	Render Container
		ourShaderProgram.Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
				
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

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		mixValue = mixValue + 0.005f;
		if (mixValue > 1)
			mixValue = 1.0f;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		mixValue = mixValue - 0.005f;
		if (mixValue < 0)
			mixValue = 0.0f;
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow * window, int width, int height)
{
	// make sure the viewport matches the new window dimensions
	glViewport(0, 0, width, height);
}