#include "Window.h"





int CALLBACK WinMain(
	HINSTANCE hInstance,
	HINSTANCE hprevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
{

	try
	{
		Window Wnd(800, 600, "Yousif Window");





		MSG Msg;
		BOOL bRet;


		while ((bRet = GetMessage(&Msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&Msg);
			DispatchMessageW(&Msg);
		}

		if (bRet == -1)
		{
			return -1;
		}

		return Msg.wParam;

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