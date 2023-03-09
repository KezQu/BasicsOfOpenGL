#pragma once
#include <iostream>
#include "GL/glew.h"

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLDEBUG(x) GLClearError();\
	x;\
	ASSERT(GLLogCall(#x, __FILE__, __LINE__))

bool GLLogCall(const char* function, const char* file, int line);
void GLClearError();
