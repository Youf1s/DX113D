#pragma once
#include"Window.h"
class App
{

	

public:
	App();

	int GO();



private:
	void DoFrame();

	Window Wnd;
	float tEst = 0.0f;
	float tEstz = 4.0f;
	
};

