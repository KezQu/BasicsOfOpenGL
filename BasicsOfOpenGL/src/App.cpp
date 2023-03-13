#include "App.h"

unsigned int App::ActiveVAO = 0;

App::App(const int width, const int height, const std::string title, const int majorVer, const int minorVer)
	:_windowWidth{width},
	_windowHeight{height},
	_windowTitle{title},
	_majorVersion{majorVer},
	_minorVersion{minorVer},
	_contextWindow{nullptr},
	_frameRate{0}
{
	if (!glfwInit())
		exit(-1);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, _majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, _minorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_contextWindow = glfwCreateWindow(_windowWidth, _windowHeight, _windowTitle.c_str(), NULL, NULL);
	
	if (!_contextWindow)
	{
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(_contextWindow);

	if (glewInit() != GLEW_OK)
		std::cout << "Error!" << std::endl;
}

App::~App()
{
	glfwDestroyWindow(_contextWindow);
	glfwTerminate();
}

void App::SetFrameRate(const int value)
{
	glfwSwapInterval(value);
}

bool App::AppRunning()
{
	return !glfwWindowShouldClose(_contextWindow);
}

void App::Refresh()
{
	glfwSwapBuffers(_contextWindow);

	glfwPollEvents();
}

void App::GetVersion() const
{
	std::cout << glGetString(GL_VERSION) << std::endl;
}

void App::GetVertexInfo()
{

	int VAid = -1;
	glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &VAid);
	std::cout << "VA:" << VAid << std::endl;

	int VBid = -1;
	glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &VBid);
	std::cout << "VB:" << VBid << std::endl;

	int IBid = -1;
	glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &IBid);
	std::cout << "IB:" << IBid << std::endl;

	std::cout << "----------------------" << std::endl;
}
