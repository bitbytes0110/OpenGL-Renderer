#include "Shader.h"

Shader::Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath)
{
	string vertexShaderString;
	string fragmentShaderString;

	unsigned int vertexShader = 0;
	unsigned int fragmentShader = 0;

	// 1. retrieve the vertex/fragment source code from filePath
	bool result = ExtractShaderCode(vertexShaderString, fragmentShaderString, vertexShaderPath, fragmentShaderPath);
	
	// 2. compile Shaders
	if (result)
	{
		result = CompileShaders(vertexShader, fragmentShader, vertexShaderString.c_str(), fragmentShaderString.c_str());
	}

	//	3. Link Shaders
	if (result)
	{
		result = LinkShaders(vertexShader, fragmentShader);
	}

	//	4. Delete Shaders

	if (result)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
	}
	if (result)
	{
		LOG("Shader Program Creation SUCCESS");
	}
	else
	{
		LOG("Shader Program Creation FAILED");
	}
}

bool Shader::ExtractShaderCode(string &vertexShaderString, string &fragmentShaderString, const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath)
{
	ifstream vShaderFile;
	ifstream fShaderFile;

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try
	{
		//	Open files
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragmentShaderPath);

		//	Read file's buffer content into streams
		stringstream vShaderStream, fShaderStream;

		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();

		//	Close file handlers
		vShaderFile.close();
		fShaderFile.close();

		//	Convert stream into strings
		vertexShaderString = vShaderStream.str();
		fragmentShaderString = fShaderStream.str();

	}
	catch (ifstream::failure e)
	{
		LOG("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
		return FAILED;
	}
	return SUCCESS;
}

bool Shader::CompileShaders(unsigned int &vertexShader, unsigned int &fragmentShader, const char* vertexShaderCode, const char* fragmentShaderCode)
{
	//	Compile Vertex Shader
	//	---------------------------------
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(vertexShader);
	if (!CheckShaderStatus(vertexShader, "VERTEX", GL_COMPILE_STATUS))
	{
		return ERROR;
	}
	
	//	Compile Fragement Shader
	//	---------------------------------
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(fragmentShader);

	if (!CheckShaderStatus(fragmentShader, "FRAGMENT", GL_COMPILE_STATUS))
	{
		return ERROR;
	}
	return SUCCESS;
}

bool Shader::LinkShaders(unsigned int vertexShader, unsigned int fragmentShader)
{
	//	Create the Shader Program by linking all other shaders
	//	---------------------------------
	ShaderProgram = glCreateProgram();
	glAttachShader(ShaderProgram, vertexShader);
	glAttachShader(ShaderProgram, fragmentShader);
	glLinkProgram(ShaderProgram);
	return CheckShaderStatus(ShaderProgram, "PROGRAM", GL_LINK_STATUS);
}

bool Shader::CheckShaderStatus(GLuint Shader, string type, GLenum state)
{
	int success;
	char infoLog[512];

	glGetShaderiv(Shader, state, &success);
	if (!success)
	{
		LOG("ERROR::SHADER");
		LOG(type);
		glGetShaderInfoLog(Shader, 512, NULL, infoLog);
		switch (state)
		{
		
		case GL_COMPILE_STATUS:
			LOG("COMPILATION_FAILED");

			break;
		case GL_LINK_STATUS:
			LOG("LINKING_FAILED");
			break;
		default:
			LOG("UNKNOWN");
		}
		LOG(infoLog);
		return FAILED;
	}
	return SUCCESS;
}

void Shader::Use()
{
	glUseProgram(ShaderProgram);
}

void Shader::SetBool(const string &name, bool bValue)
{
	glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), bValue);
}

void Shader::SetInt(const string &name, int iValue)
{
	glUniform1i(glGetUniformLocation(ShaderProgram, name.c_str()), iValue);
}

void Shader::SetFloat(const string &name, float fValue)
{
	glUniform1f(glGetUniformLocation(ShaderProgram, name.c_str()), fValue);
}


Shader::~Shader()
{
	LOG("Shader Destroyed.");
}