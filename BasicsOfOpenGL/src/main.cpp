#include "VertexArray.h"

int main()
{
	App mainApp(1280, 720, "Main");
	mainApp.SetFrameRate(3);
	mainApp.GetVersion();
	
	App::GetVertexInfo();

	//VertexArray va;
	//va.Bind();

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

	//va.Unbind();

	App::GetVertexInfo();

	//va.AddBuffer(&ib, &vb);
	vb.Bind(0,0);
	ib.Bind();

	App::GetVertexInfo();

	const auto& layouts = vb.GetLayout().GetElements();
	for (int i = 0; i < layouts.size(); ++i)
	{
		GLDEBUG(glEnableVertexAttribArray(i));
		GLDEBUG(glVertexAttribFormat(i, layouts[i]._dim, layouts[i]._type, layouts[i]._normalize, layouts[i]._relativeoffset));
		GLDEBUG(glVertexAttribBinding(i, 0));
	}

	while (mainApp.AppRunning())
	{
		GLDEBUG(glClear(GL_COLOR_BUFFER_BIT));

		GLDEBUG(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

		mainApp.Refresh();
	}
	return 0;
}