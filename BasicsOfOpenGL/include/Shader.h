#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

#include "GL_Debug.h"

struct ShaderInfo
{
	std::string _shaderSource;
	unsigned int _shaderID;
	GLenum _type;
};


class Shader
{
private:
	unsigned int _programID;
	std::vector<std::string> _shaderPath;
	std::vector<ShaderInfo> _shaderList;
	std::unordered_map<std::string, int> _uniformList;
public:
	Shader(const std::string& shaderPath="");
	~Shader();
	
	void Bind() const;
	void Unbind() const;
	const unsigned int GetProgramID() const;
	void AddShaders(const std::string& shaderPath);
	void LinkProgram() const;

	int GetUniformLocation(const std::string& uniformName);
private:
	void DivShaders(const std::string& shaderPath);
	void CreateShaders(const std::string& shaderPath);
	unsigned int CompileShader(const ShaderInfo& shader) const;
};
