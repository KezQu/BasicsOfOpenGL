#pragma once

#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include <vector>

#include "GL_Debug.h"

#include "App.h"

template<typename>
constexpr bool dependent_false = false;

template <typename T> 
class Buffer
{
	Buffer() 
	{ 
		std::cout << "Type not supported" << std::endl;
		static_assert(dependent_false<T>); 
	}
};
template<> 
class Buffer<float>
{
protected:
	unsigned int _rendererID;
	std::vector<float> _data;
public:
	virtual const unsigned int GetID() const;
	virtual const unsigned int GetBufferCount() const;
	virtual const unsigned int GetBufferSize() const;
	virtual void Bind(const unsigned int index, const unsigned int VAid) const = 0;
	virtual void Unbind(const unsigned int VAid) const = 0;
protected:
	Buffer(const std::vector<float>& data);
	Buffer(const float* data, const unsigned int count);
	~Buffer();
};
template<>
class Buffer<unsigned int>
{
protected:
	unsigned int _rendererID;
	std::vector<unsigned int> _data;
public:
	virtual const unsigned int GetID() const;
	virtual const unsigned int GetBufferCount() const;
	virtual const unsigned int GetBufferSize() const;
	virtual void Bind() const = 0;
	virtual void Unbind() const = 0;
protected:
	Buffer(const std::vector<unsigned int>& data);
	Buffer(const unsigned int* data, const unsigned int count);
	~Buffer();
};


