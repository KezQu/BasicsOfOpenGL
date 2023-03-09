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
template<>
void VBLayout::AddLayout<float>(const int dim)
{
	VBElements tmp= { GL_FLOAT, dim, _layout.size() != 0 ? _layout.back().SizeOfType() * _layout.back()._dim : 0, GL_FALSE };
	_layout.push_back(tmp);
	_stride += _layout.back().SizeOfType() * dim;
}
template<>
void VBLayout::AddLayout<unsigned int>(const int dim)
{
	VBElements tmp = { GL_UNSIGNED_INT, dim, _layout.size() != 0 ? _layout.back().SizeOfType() * _layout.back()._dim : 0, GL_FALSE };
	_layout.push_back(tmp);
	_stride += _layout.back().SizeOfType() * dim;

}
template<>
void VBLayout::AddLayout<unsigned char>(const int dim)
{
	VBElements tmp = { GL_UNSIGNED_BYTE, dim, _layout.size() != 0 ? _layout.back().SizeOfType() * _layout.back()._dim : 0, GL_FALSE };
	_layout.push_back(tmp);
	_stride += _layout.back().SizeOfType() * dim;
}

