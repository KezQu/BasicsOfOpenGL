#include "Shader.h"

Shader::Shader(const std::string& shaderPath)
	:_programID{0},
	_shaderPath{ {shaderPath} }
{
	GLDEBUG(_programID = glCreateProgram());
	if (shaderPath != "")
		AddShaders(shaderPath);
}

Shader::~Shader()
{
	GLDEBUG(glDeleteProgram(_programID));
}

void Shader::Bind() const
{
	GLDEBUG(glUseProgram(_programID));
}

void Shader::Unbind() const
{
	GLDEBUG(glUseProgram(0));
}

const unsigned int Shader::GetProgramID() const
{
	return _programID;
}

void Shader::AddShaders(const std::string& shaderPath)
{
	DivShaders(shaderPath);
	CreateShaders(shaderPath);
}

void Shader::LinkProgram() const
{
	GLDEBUG(glLinkProgram(_programID));
	GLDEBUG(glValidateProgram(_programID));
	for (auto shader : _shaderList)
	{
	//	GLDEBUG(glDetachShader(_programID, shader._shaderID));
		GLDEBUG(glDeleteShader(shader._shaderID));
	}
}

int Shader::GetUniformLocation(const std::string& uniformName)
{

	if (_uniformList.find(uniformName) == _uniformList.end())
		return _uniformList[uniformName];
	
	GLDEBUG(_uniformList[uniformName] = glGetUniformLocation(_programID, uniformName.c_str()));
	if(_uniformList[uniformName] == -1)
		std::cout << "Warning!!! Uniform: " << uniformName << "does not exist." << std::endl;
	
	return _uniformList[uniformName];
}

void Shader::CreateShaders(const std::string& shaderPath)
{
	for (auto shader : _shaderList)
	{
		const char* src = shader._shaderSource.c_str();
		GLDEBUG(shader._shaderID = glCreateShader(shader._type));
		GLDEBUG(glShaderSource(shader._shaderID, 1, &src, nullptr));
		CompileShader(shader);
	}
}

unsigned int Shader::CompileShader(const ShaderInfo& shader) const
{
	int compiled = GL_FALSE;
	GLDEBUG(glCompileShader(shader._shaderID));

	GLDEBUG(glGetShaderiv(shader._shaderID, GL_COMPILE_STATUS, &compiled));
	if (compiled)
	{
		GLDEBUG(glAttachShader(_programID, shader._shaderID));
	}
	else
	{
		int length;
		GLDEBUG(glGetShaderiv(shader._shaderID, GL_INFO_LOG_LENGTH, &length));
		char* message = new char[length];
		GLDEBUG(glGetShaderInfoLog(shader._shaderID, length, &length, message));
		std::cout << "Failed to compile " << (shader._type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
		std::cout << message << std::endl;
		GLDEBUG(glDeleteShader(shader._shaderID));
		delete[] message;
		return 0;
	}
	return shader._shaderID;
}

void Shader::DivShaders(const std::string& shaderPath)
{
	std::ifstream shaderFile(shaderPath);
	std::string line;
	std::stringstream shaderStream;
	GLenum tmpType = GL_NONE;

	while (getline(shaderFile,line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			switch (tmpType)
			{
			case GL_NONE:
				break;
			case GL_VERTEX_SHADER:
				_shaderList.push_back({ shaderStream.str(), 0, GL_VERTEX_SHADER });
				shaderStream.str(std::string());
				tmpType = GL_NONE;
				break;
			case GL_FRAGMENT_SHADER:
				_shaderList.push_back({ shaderStream.str(), 0, GL_FRAGMENT_SHADER });
				shaderStream.str(std::string());
				tmpType = GL_NONE;
				break;
			}
			if (line.find("vertex") != std::string::npos)
				tmpType = GL_VERTEX_SHADER;

			if (line.find("fragment") != std::string::npos)
				tmpType = GL_FRAGMENT_SHADER;
		}
		else
			shaderStream << line << std::endl;
	}
	switch (tmpType)
	{
	case GL_NONE:
		break;
	case GL_VERTEX_SHADER:
		_shaderList.push_back({ shaderStream.str(), 0, GL_VERTEX_SHADER });
		shaderStream.str(std::string());
		tmpType = GL_NONE;
		break;
	case GL_FRAGMENT_SHADER:
		_shaderList.push_back({ shaderStream.str(), 0, GL_FRAGMENT_SHADER });
		shaderStream.str(std::string());
		tmpType = GL_NONE;
		break;
	}
}
