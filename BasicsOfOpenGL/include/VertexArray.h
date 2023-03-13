#pragma once

#include "IndexBuffer.h"
#include "VertexBuffer.h"

struct IndexVertexPair
{
	const IndexBuffer* _ib;
	const VertexBuffer* _vb;
};

class VertexArray
{
private:
	std::vector<IndexVertexPair> _Vbuffers;
	unsigned int _rendererID;
	mutable int _activeBuffer;
public:
	VertexArray();
	~VertexArray();

	const unsigned int GetID() const;
	const IndexBuffer& GetIB(const unsigned int index) const;
	const VertexBuffer& GetVB(const unsigned int index) const;
	const unsigned int GetIBCount(const unsigned int index) const;
	const int GetActiveBufferID() const;

	void Bind() const;
	void Unbind() const;
	
	const unsigned int AddBuffers(const IndexBuffer* ib, const VertexBuffer* vb);
	void SwapBuffers(const int index) const;
	
	void DisableArray(const unsigned int index) const;
	void EnableArray(const unsigned int index) const;
};

