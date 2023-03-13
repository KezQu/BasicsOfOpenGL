#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

class App
{
private:
	std::string _windowTitle;
	int _windowWidth;
	int _windowHeight;
	int _majorVersion;
	int _minorVersion;
	int _frameRate;
	GLFWwindow* _contextWindow;
public:
	static unsigned int ActiveVAO;
public:
	App(const int width, const int height, const std::string title, const int majorVer = 4, const int minorVer = 6);
	~App();

	void SetFrameRate(const int value);
	bool AppRunning();
	void Refresh();
	void GetVersion() const;

	static void GetVertexInfo();
};

