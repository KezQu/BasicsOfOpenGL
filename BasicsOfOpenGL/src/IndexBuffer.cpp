#include "IndexBuffer.h"

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& data)
	:Buffer<unsigned int>{data}
{
	GLDEBUG(glGenBuffers(1, &_rendererID));
	Bind();
	GLDEBUG(glNamedBufferData(_rendererID, GetBufferSize(), _data.data(), GL_STATIC_DRAW));
	Unbind();
}

IndexBuffer::~IndexBuffer()
{
	GLDEBUG(glDeleteBuffers(1, &_rendererID));
}

void IndexBuffer::Bind() const
{
	GLDEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _rendererID));
}

void IndexBuffer::Unbind() const
{
	GLDEBUG(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}

const unsigned int IndexBuffer::GetCount() const
{
	return _data.size();
}

const unsigned int* IndexBuffer::GetData() const
{
	return _data.data();
}
