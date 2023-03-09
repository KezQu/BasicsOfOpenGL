#pragma once

#include "Buffer.h"
#include "VBLayout.h"

class VertexBuffer: public Buffer<float>
{
private:
	VBLayout _layout;
	mutable int _bindingIndex;
public:
	VertexBuffer(const std::vector<float>& data = {}, const std::vector<unsigned int> dimVec = {});
	~VertexBuffer();

	void Bind(const unsigned int index, const unsigned int VAid) const override;
	void Unbind(const unsigned int VAid) const override;
	const VBLayout& GetLayout() const;
};

