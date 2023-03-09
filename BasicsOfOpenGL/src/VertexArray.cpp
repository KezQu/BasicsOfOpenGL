#include "VertexArray.h"

VertexArray::VertexArray()
	:_activeBuffer{-1}
{
	GLDEBUG(glGenVertexArrays(1, &_rendererID));
}

VertexArray::~VertexArray()
{
	GLDEBUG(glDeleteVertexArrays(1, &_rendererID));
}

const unsigned int VertexArray::GetID() const
{
	return _rendererID;
}

const IndexBuffer& VertexArray::GetIB(const unsigned int index) const
{
	return *(_Vbuffers[index]._ib);
}

const VertexBuffer& VertexArray::GetVB(const unsigned int index) const
{
	return *(_Vbuffers[index]._vb);
}

const unsigned int VertexArray::GetIBSize(const unsigned int index) const
{
	return GetIB(index).GetCount();
}

const int VertexArray::GetActiveBufferID() const
{
	return _activeBuffer;
}

void VertexArray::Bind() const
{
	GLDEBUG(glBindVertexArray(_rendererID));
	App::ActiveVAO = _rendererID;
}

void VertexArray::Unbind() const
{
	GLDEBUG(glBindVertexArray(0));
	App::ActiveVAO = 0;
}

void VertexArray::AddBuffer(const IndexBuffer* ib, const VertexBuffer* vb)
{
	int maxBufferSize = 0;
	GLDEBUG(glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &maxBufferSize));
	std::cout << maxBufferSize << std::endl;
	if(_Vbuffers.size() == maxBufferSize)
	{
		std::cout << "Number of VertexBuffer overflow !!!" << std::endl;
		ASSERT(false);
	}

	IndexVertexPair tmp_pair = { ib,vb };
	_Vbuffers.push_back(tmp_pair);

	Bind();
	SwapBuffers(_Vbuffers.size() - 1);
}

inline void VertexArray::DisableArray(const unsigned int index) const
{
	GLDEBUG(glDisableVertexAttribArray(index));
}

inline void VertexArray::EnableArray(const unsigned int index) const
{
	GLDEBUG(glEnableVertexAttribArray(index));
}

void VertexArray::SwapBuffers(const unsigned int index) const
{
	if(_activeBuffer != -1)
	{
		_Vbuffers[_activeBuffer]._vb->Unbind(_rendererID);
		_Vbuffers[_activeBuffer]._ib->Unbind();

		const auto& layouts = _Vbuffers[_activeBuffer]._vb->GetLayout().GetElements();
		for (int i = 0; i < layouts.size(); ++i)
		{
			GLDEBUG(glDisableVertexAttribArray(i));
		}
	}
	_Vbuffers[index]._vb->Bind(index, _rendererID);
	_Vbuffers[index]._ib->Bind();

	const auto& layouts = _Vbuffers[index]._vb->GetLayout().GetElements();
	for (int i = 0; i < layouts.size(); ++i)
	{
		GLDEBUG(glEnableVertexAttribArray(i));
		GLDEBUG(glVertexAttribFormat(i, layouts[i]._dim, layouts[i]._type, layouts[i]._normalize, layouts[i]._relativeoffset));
		GLDEBUG(glVertexAttribBinding(i, index));
	}

	_activeBuffer = index;
}
