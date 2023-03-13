#pragma once

#include <vector>
#include <iostream>
#include "GL/glew.h"

#include "GL_Debug.h"

struct VBElements
{
	unsigned int _type;
	unsigned int _dim;
	unsigned int _relativeoffset;
	bool _normalize;
	unsigned int SizeOfType()
	{
		switch (_type)
		{
			case GL_FLOAT:			return 4;
			case GL_UNSIGNED_INT:	return 4;
			case GL_UNSIGNED_BYTE:	return 1;
		}
	}
};

template<typename>
constexpr bool dependent_false2 = false;

class VBLayout
{
private:
	std::vector<VBElements> _layout;
	unsigned int _stride;
public:
	VBLayout();
	~VBLayout();

	const unsigned int GetStride() const;
	const std::vector<VBElements>& GetElements() const;

	template<typename T>
	void AddLayout(const int dim)
	{
		std::cout << "Type for verticies not supported" << std::endl;
		static_assert(dependent_false2<T>);
	}
	template<>
	void AddLayout<float>(const int dim);
	template<>
	void AddLayout<unsigned int>(const int dim);
	template<>
	void AddLayout<unsigned char>(const int dim);

	const bool CheckAttribOverflow() const;
};

