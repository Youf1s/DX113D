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
	Wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f, 1.0f);
	Wnd.Gfx().EndFrame();
	
}
