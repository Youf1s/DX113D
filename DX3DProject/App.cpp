#include "App.h"
#include"Cube.h"
#include <random>

App::App()
	:
	Wnd(1920,1080,"Yousif Window")
{
	std::mt19937 rng(std::random_device{}());
	std::uniform_real_distribution<float> adist(0.0f, 3.1415f * 1.0f);
	std::uniform_real_distribution<float> ddist(0.0f, 3.1415f * 1.0f);
	std::uniform_real_distribution<float> odist(0.0f, 3.1415f * 0.3f);
	std::uniform_real_distribution<float> rdist(6.0f, 20.0f);
	for (auto i = 0; i < 100; i++)
	{
		Cubes.push_back(std::make_unique<Cube>(
			Wnd.Gfx(), rng, adist,
			ddist, odist, rdist
			));
	}
	Wnd.Gfx().SetProjection(DirectX::XMMatrixPerspectiveLH(2.0f, 16.0f / 9.0f, 0.5f, 40.0f));
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

App::~App()
{
}

void App::DoFrame()
{
	auto DST = timer.Mark();
	Wnd.Gfx().ClearBuffer(0.0f, 0.0f, 0.0f, 1.0f);
	for (auto& b : Cubes)
	{
		b->Update(DST);
		b->DrawItt(Wnd.Gfx());
	}
	Wnd.Gfx().EndFrame();
	
}
