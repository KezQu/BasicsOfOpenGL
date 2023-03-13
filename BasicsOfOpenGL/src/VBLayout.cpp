#include "VBLayout.h"

VBLayout::VBLayout()
	:_stride{0}
{}
VBLayout::~VBLayout()
{}
const unsigned int VBLayout::GetStride() const
{
	return _stride;
}
const std::vector<VBElements>& VBLayout::GetElements() const
{
	return _layout;
}
const bool VBLayout::CheckAttribOverflow() const
{
	int maxBufferSize = 0;
	GLDEBUG(glGetIntegerv(GL_MAX_VERTEX_ATTRIB_BINDINGS, &maxBufferSize));
	std::cout << maxBufferSize << std::endl;
	if (_layout.size() == maxBufferSize)
	{
		std::cout << "Number of VertexBuffer overflow !!!" << std::endl;
		return false;
	}
	return true;
}
template<>
void VBLayout::AddLayout<float>(const int dim)
{
	ASSERT(CheckAttribOverflow());
	VBElements tmp= { GL_FLOAT, dim, _layout.size() != 0 ? _layout.back().SizeOfType() * _layout.back()._dim : 0, GL_FALSE };
	_layout.push_back(tmp);
	_stride += _layout.back().SizeOfType() * dim;
}
template<>
void VBLayout::AddLayout<unsigned int>(const int dim)
{
	ASSERT(CheckAttribOverflow());
	VBElements tmp = { GL_UNSIGNED_INT, dim, _layout.size() != 0 ? _layout.back().SizeOfType() * _layout.back()._dim : 0, GL_FALSE };
	_layout.push_back(tmp);
	_stride += _layout.back().SizeOfType() * dim;

}
template<>
void VBLayout::AddLayout<unsigned char>(const int dim)
{
	ASSERT(CheckAttribOverflow());
	VBElements tmp = { GL_UNSIGNED_BYTE, dim, _layout.size() != 0 ? _layout.back().SizeOfType() * _layout.back()._dim : 0, GL_FALSE };
	_layout.push_back(tmp);
	_stride += _layout.back().SizeOfType() * dim;
}

