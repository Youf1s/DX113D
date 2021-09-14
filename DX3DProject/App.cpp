#include "App.h"

App::App()
	:
	Wnd(1920,1080,"Yousif Window")
{
}

int App::GO()
{
	while (true)
	{
		if (const auto MCode = Window::ProcMsg())
		{
			return *MCode;
		}
		DoFrame();
	}

}

void App::DoFrame()
{
	if (Wnd.KBD.KeyIsPressed(VK_LEFT))
	{
		tEst = tEst + 0.1f;
	}
	if (Wnd.KBD.KeyIsPressed(VK_RIGHT))
	{
		tEst = tEst - 0.1f;
	}
	if (Wnd.KBD.KeyIsPressed(VK_UP))
	{
		tEstz -= 0.1f;
	}
	if (Wnd.KBD.KeyIsPressed(VK_DOWN))
	{
		tEstz += 0.1f;
	}
	Wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f, 1.0f);
	Wnd.Gfx().DrawTestTri( tEst,
		0.0f,
		0.0f,
		4.0f);
	Wnd.Gfx().DrawTestTri(tEst,
		Wnd.MUS.GetPosX() / 960.0f - 1.0f,
		-Wnd.MUS.GetPosY() / 540.0f + 1.0f,
		tEstz);
	Wnd.Gfx().EndFrame();
	
}
