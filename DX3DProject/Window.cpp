#include "Window.h"
#include <sstream>
#include"resource.h"




Window::WindowClass Window::WindowClass::wndClass;

Window::WindowClass::WindowClass()
	:
	hInst(GetModuleHandle(nullptr))
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = HandleMsgSetup;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = GetInstance();
	wc.hIcon = reinterpret_cast<HICON>(LoadImage(hInst,MAKEINTRESOURCE(IDI_DUCK),IMAGE_ICON,48,48,0));
	wc.hCursor = nullptr;
	wc.hbrBackground = nullptr;
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = GetName();
	wc.hIconSm = reinterpret_cast<HICON>(LoadImage(hInst, MAKEINTRESOURCE(IDI_DUCK), IMAGE_ICON, 48, 48, 0));
	RegisterClassEx(&wc);
}

Window::WindowClass::~WindowClass()
{
	UnregisterClass(wndClassName, GetInstance());
}

const char* Window::WindowClass::GetName()
{
	return wndClassName;
}

HINSTANCE Window::WindowClass::GetInstance()
{
	return wndClass.hInst;
}



Window::Window(int X, int Y, const char* name)
{
	
	RECT WR;
	WR.left = 100;
	WR.right = X + WR.left;
	WR.top = 100;
	WR.bottom = Y + WR.top;
	AdjustWindowRect(&WR, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME, FALSE);
	HWnd = CreateWindow(
		WindowClass::GetName(), name,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU | WS_THICKFRAME,
		CW_USEDEFAULT, CW_USEDEFAULT, WR.right - WR.left, WR.bottom - WR.top,
		nullptr, nullptr, WindowClass::GetInstance(), this
	);
	if (HWnd == nullptr)
	{
		throw YOUSIF_LAST_ERROR();
	}
	
	ShowWindow(HWnd, SW_SHOWDEFAULT);
}

Window::~Window()
{
	DestroyWindow(HWnd);
}

LRESULT WINAPI Window::HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) 
{
	
	if (msg == WM_NCCREATE)
	{
		
		const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
		Window* const pWnd = static_cast<Window*>(pCreate->lpCreateParams);
		
		SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWnd));
	
		SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(&Window::HandleMsgRe));
		
		return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
	}
	
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

LRESULT WINAPI Window::HandleMsgRe(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	
	Window* const pWnd = reinterpret_cast<Window*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
	
	return pWnd->HandleMsg(hWnd, msg, wParam, lParam);
}

LRESULT Window::HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(0);
		return 0;
	case WM_KILLFOCUS:
		KBD.ClearSt();
	case WM_KEYDOWN:
	case WM_SYSKEYDOWN:
		KBD.OnKeyPressed(static_cast<unsigned char>(wParam));
		if (!(lParam & 0x40000000) || KBD.IsAutoRepeatActive())
		{
			KBD.OnKeyPressed(static_cast<unsigned char>(wParam));
		}
		break;
	case WM_KEYUP:
	case WM_SYSKEYUP:
		KBD.OnKeyReleased(static_cast<unsigned char>(wParam));
		break;
	case WM_CHAR:
		KBD.OnChar(static_cast<unsigned char>(wParam));
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}






///////////////// Eror Handling /////////////////////

Window::Errors::Errors(int Line, const char* File, HRESULT HR) noexcept
			:
		YousifError(Line,File),
		HR(HR)
			
{}

const char* Window::Errors::what() const noexcept
{
	std::ostringstream OS;
	OS<< GetType() << std::endl << "Error Code : " << GetError() << std::endl <<
		"Description : " << GetErrorStr() <<
		std::endl<< GetOrSt();
	WtBuf = OS.str();

	return WtBuf.c_str();
}

const char* Window::Errors::GetType() const noexcept
{
	return "Yousif Window Error";
}

std::string Window::Errors::TransError(HRESULT HR) noexcept
{
	char* MsgBuf = nullptr;
	DWORD MsgLen = FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM |
	FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, HR, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
	reinterpret_cast<LPSTR>(&MsgBuf), 0, nullptr);
	if (MsgLen == 0)
	{
		return "Unkown Error Code !";
	}
	std::string ErrorSt = MsgBuf;
	LocalFree(MsgBuf);
	return ErrorSt;
}

HRESULT Window::Errors::GetError() const noexcept
{
	return HR;
}

std::string Window::Errors::GetErrorStr() const noexcept
{
	return TransError(HR);
}
