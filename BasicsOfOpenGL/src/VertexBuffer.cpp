#include "VertexBuffer.h"
#include "App.h"

VertexBuffer::VertexBuffer(const std::vector<float>& data, const std::vector<unsigned int> dimVec)
	:Buffer<float>{data},
	_bindingIndex{-1},
	_layout{}
{
	GLDEBUG(glGenBuffers(1, &_rendererID));
	Bind(15, App::ActiveVAO);
	GLDEBUG(glNamedBufferData(_rendererID, GetBufferSize(), _data.data(), GL_STATIC_DRAW));

	for(auto dim : dimVec)
		_layout.AddLayout<float>(dim);

	Unbind(App::ActiveVAO);
}

VertexBuffer::~VertexBuffer()
{
	GLDEBUG(glDeleteBuffers(1, &_rendererID));
}

void VertexBuffer::Bind(const unsigned int index, const unsigned int VAid) const
{
	_bindingIndex = index;
	GLDEBUG(glBindVertexBuffer(index, _rendererID, 0, _layout.GetStride()));
	//GLDEBUG(glVertexArrayVertexBuffer(VAid, index, _rendererID, 0, _layout.GetStride()));
}

void VertexBuffer::Unbind(const unsigned int VAid) const
{
	GLDEBUG(glBindVertexBuffer(_bindingIndex, 0, 0, _layout.GetStride()));
	//GLDEBUG(glVertexArrayVertexBuffer(VAid, _bindingIndex, 0, 0, _layout.GetStride()));
	_bindingIndex = -1;
}

const VBLayout& VertexBuffer::GetLayout() const
{
	return _layout;
}
