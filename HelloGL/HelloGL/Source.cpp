#include<glad\glad.h>
#include<GLFW\glfw3.h>

#include<iostream>

#define WIDTH	1280
#define HEIGHT  720

#define DEBUG(printString) std::cout<< printString<< std::endl;

//	GLSL
const char *vertexShaderSource = "#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aCol;\n"
"out vec3 vertexColor;"

"void main()\n"
"{\n"
"	gl_Position = vec4(aPos, 1.0f);\n"
"	vertexColor = aCol;"
"}\n\0";

const char *fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 vertexColor;\n"
"void main()\n"
"{\n"
"	FragColor = vec4(vertexColor, 1.0f);\n"
"}\n\0";

// End of GLSL



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


	float vertices[] = {
		0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, 0.0f,0.0f, 1.0f, 0.0f,
		0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f
	};
	unsigned int indices[] = {  // note that we start from 0!
		2, 1, 0,   // first triangle
	};


	//	Vertex Buffer Object		( Stores all vertex data )
	unsigned int VBO;
	glGenBuffers(1, &VBO);

	//	Vertex Array Object			( Stores all the vertex object attributes and also links all the  VBOs and EBOs )
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);

	//	Elementary Buffer object	( Stores all indices )
	unsigned int EBO;
	glGenBuffers(1, &EBO);




	glBindVertexArray(VAO);


	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Setting the vertex attributes (how the vertex data should be interpreted)
	glVertexAttribPointer(0,3, GL_FLOAT,GL_FALSE,6*(sizeof(GL_FLOAT)),(void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1,3, GL_FLOAT, GL_FALSE, 6*(sizeof(GL_FLOAT)),(void*)(3*sizeof(float)) );
	glEnableVertexAttribArray(1);

	//	Vertex Shader
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);


	int success;
	char log[256];

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		DEBUG("ERROr");

	}

	// Fragment Shader

	
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	glShaderSource(fragmentShader,1, &fragmentShaderSource, NULL );
	glCompileShader(fragmentShader);


	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, log);
		DEBUG(log);

	}

	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	
	glBindVertexArray(0);	// Unbinds the Vertex Array object


	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	while (!glfwWindowShouldClose(window))	// Game Loop
	{
		processInput(window);

		// Rendering code

		glClearColor(0.2f,0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		/*float timeValue = glfwGetTime();
		float redValue = (sin(timeValue) / 2) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "vertexColor");
		*/
		glUseProgram(shaderProgram);
		//glUniform3f(vertexColorLocation, redValue, 0.0f, 0.0f);
		glBindVertexArray(VAO);


		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	//	Enables Wireframe mode
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	//	Disables Wireframe mode

		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		// End of Rendering Code


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