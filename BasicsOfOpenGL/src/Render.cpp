#include "Render.h"

void Render::Clear() const
{
	GLDEBUG(glClear(GL_COLOR_BUFFER_BIT));
}

void Render::Draw(const VertexArray& vertexArray, const Shader& shader, const int bufferID) const
{
	shader.LinkProgram();
	shader.Bind();
	vertexArray.Bind();
	vertexArray.SwapBuffers(bufferID);
	;
	GLDEBUG(glDrawElements(GL_TRIANGLES, vertexArray.GetIBCount(bufferID), GL_UNSIGNED_INT, nullptr));
}
