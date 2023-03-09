#pragma once

#include "Buffer.h"

class IndexBuffer: public Buffer<unsigned int>
{
public:
	IndexBuffer(const std::vector<unsigned int>& data = {});
	~IndexBuffer();
	void Bind() const override;
	void Unbind() const override;
	const unsigned int GetCount() const;
	const unsigned int* GetData() const;
};

