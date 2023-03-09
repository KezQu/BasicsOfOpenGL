#include "Buffer.h"

Buffer<float>::Buffer(const std::vector<float>& data)
	:_data{data},
	_rendererID{0}
{}
Buffer<float>::Buffer(const float* data, const unsigned int count)
	:_rendererID{0}
{
	for (unsigned int i = 0; i < count; i++)
		_data.push_back(data[i]);
}
Buffer<float>::~Buffer() 
{
	_data.clear();
}
const unsigned int Buffer<float>::GetID() const
{
	return _rendererID;
}
const unsigned int Buffer<float>::GetBufferCount() const
{
	return _data.size();
}
const unsigned int Buffer<float>::GetBufferSize() const
{
	return _data.size() * sizeof(float);
}

Buffer<unsigned int>::Buffer(const std::vector<unsigned int>& data)
	:_data{data},
	_rendererID{ 0 }
{
}
Buffer<unsigned int>::Buffer(const unsigned int* data, const unsigned int count)
	: _rendererID{ 0 }
{
	for (unsigned int i = 0; i < count; i++)
		_data.push_back(data[i]);
}
Buffer<unsigned int>::~Buffer()
{
	_data.clear();
}
const unsigned int Buffer<unsigned int>::GetID() const
{
	return _rendererID;
}
const unsigned int Buffer<unsigned int>::GetBufferCount() const
{
	return _data.size();
}
const unsigned int Buffer<unsigned int>::GetBufferSize() const
{
	return _data.size() * sizeof(unsigned int);
}