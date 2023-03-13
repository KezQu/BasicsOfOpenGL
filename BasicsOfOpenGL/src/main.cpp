#include "Render.h"

int main()
{
	App mainApp(1280, 720, "Main");
	mainApp.SetFrameRate(3);
	mainApp.GetVersion();
	
	App::GetVertexInfo();

	VertexArray va;
	va.Bind();

	App::GetVertexInfo();

	std::vector<float> vertices =
	{ -0.5f, -0.5f,
		0.5f, 0.5f,
		-0.5f, 0.5f,
		0.5f, -0.5f
	};
	VertexBuffer vb(vertices,{2});

	std::vector<unsigned int> indices =
	{
		0,2,1,3,0,2
	};

	IndexBuffer ib(indices);
	
	App::GetVertexInfo();

	va.Unbind();

	App::GetVertexInfo();

	va.AddBuffers(&ib, &vb);

	App::GetVertexInfo();

	Shader shader1("shaders/basic.shader");

	Render render1;

	while (mainApp.AppRunning())
	{
		render1.Clear();

		render1.Draw(va, shader1, 0);

		mainApp.Refresh();
	}
	return 0;
}