#pragma once

#include<glad/glad.h>
#include"Macros.h"
		
#include<String>
#include<iostream>
#include<fstream>
#include<sstream>

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
	
	~Shader();

private:

	bool ExtractShaderCode(string& vertexShaderString, string& fragmentShaderString, const GLchar * vertexShaderPath, const GLchar * fragmentShaderPath);
	bool CompileShaders(unsigned int &vertexShader, unsigned int &fragmentShader, const char* vertexShaderCode, const char* fragmentShaderCode);
	bool LinkShaders(unsigned int vertexShader, unsigned int fragmentShader);
	
	bool CheckShaderStatus(GLuint Shader, string type, GLenum state);
};