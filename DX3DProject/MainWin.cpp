#include "Window.h"
#include"App.h"




int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hprevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	try
	{

		return App().GO();

	}
	catch (const YousifError& Y)
	{
		MessageBox(nullptr, Y.what() , Y.GetType(), MB_OK | MB_ICONEXCLAMATION);

	}
	catch (const std::exception& Y)
	{
		MessageBox(nullptr, Y.what(), "Standerd Error", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No Details ", "Unkown Error", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;



}

