#pragma once

#include "Shader.h"
#include "VertexArray.h"

class Render
{
public:
	void Clear() const;
	void Draw(const VertexArray& vertexArray,const Shader& shader, const int bufferID) const;
};

