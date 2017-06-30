#pragma once

#include<glad/glad.h>
#include"Macros.h"
		
#include<String>
#include<iostream>
#include<fstream>
#include<sstream>

#include<glm\glm.hpp>
#include<glm\gtc\matrix_transform.hpp>
#include<glm\gtc\type_ptr.hpp>

using namespace std;

class Shader
{
public:

	unsigned int ShaderProgram;

	//	Constructor reads and builds the data
	Shader(const GLchar* vertexShaderPath, const GLchar* fragmentShaderPath);

	// Activate the shader
	void Use();

	//	Utility uniform functions
	void SetBool(const string &name, bool bValue);
	void SetInt(const string &name, int iValue);
	void SetFloat(const string &name, float fValue);
	void SetMat4(const string &name, glm::mat4 fValue);
	
	~Shader();

private:

	bool ExtractShaderCode(string& vertexShaderString, string& fragmentShaderString, const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath);
	bool CompileShaders(unsigned int &vertexShader, unsigned int &fragmentShader, const char* vertexShaderCode, const char* fragmentShaderCode);
	bool LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);
	
	bool CheckShaderStatus(GLuint Shader, string type, GLenum state);
};