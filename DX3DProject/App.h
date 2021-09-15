#pragma once
#include"Window.h"
#include "Timer.h"
class App
{

	

public:
	App();

	int GO();

	~App();

private:
	void DoFrame();

	Window Wnd;
	Timer timer;
	std::vector<std::unique_ptr<class Cube>> Cubes;
};

