#include "App.h"

App::App()
	:
	Wnd(800,600,"Yousif Window")
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
	Wnd.Gfx().EndFrame();
	Wnd.Gfx().ClearBuffer(0.7f, 0.2f, 0.1f, 1.0f);
}
