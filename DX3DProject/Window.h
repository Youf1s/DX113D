#pragma once
#include "YousifWin.h"
#include "YousifErrorHandling.h"
#include "Keyboard.h"
#include "Mouse.h"
#include"Graphics.h"
#include<optional>
#include<memory>



class Window
{
public:
	class Errors : public YousifError
	{
		using YousifError::YousifError;
	public:
		static std::string TransError(HRESULT HR) noexcept;
	};

	class HrErrors : public Errors 
	{
	public:
		HrErrors(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetError() const noexcept;
		std::string GetErrorStr()const noexcept;
	private:
		HRESULT hr;
	};

	class NoGfxErrors : public Errors 
	{
	public:
		using Errors::Errors;
		 const char* GetType() const noexcept override;
	};



private:
	
	class WindowClass
	{
	public:
		static const char* GetName();
		static HINSTANCE GetInstance();
	private:
		WindowClass();
		~WindowClass();
		WindowClass(const WindowClass&) = delete;
		WindowClass& operator=(const WindowClass&) = delete;
		static constexpr const char* wndClassName = "YousifDX";
		static WindowClass wndClass;
		HINSTANCE hInst;
	};
public:
	Window(int X, int Y, const char* name);
	~Window();
	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
	void SetTitle(const std::string& title);

	static std::optional<int> ProcMsg() noexcept;
	
	Graphics& Gfx();

	Keyboard KBD;
	Mouse MUS;
private:
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	static LRESULT WINAPI HandleMsgRe(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) noexcept;
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam ) noexcept;
private:
	int X;
	int Y;
	std::unique_ptr<Graphics> pGfx;
	HWND HWnd;
};


#define YOUSIF_ERROR(hr) Window::HrErrors(__LINE__,__FILE__,(hr))
#define YOUSIF_LAST_ERROR() Window::HrErrors(__LINE__,__FILE__,GetLastError())
#define YOUSIF_NOGFX_ERROR() Window::NoGfxErrors(__LINE__,__FILE__)