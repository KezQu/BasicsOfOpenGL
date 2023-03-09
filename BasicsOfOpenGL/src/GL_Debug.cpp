#include "GL_Debug.h"

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}
bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "Error: " << error << std::endl;
		std::cout << "In file: " << file << std::endl;
		std::cout << "In function: " << function << std::endl;
		std::cout << "In line: " << line << std::endl;
		return false;
	}
	return true;
}