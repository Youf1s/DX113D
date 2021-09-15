#pragma once
#include "YousifWin.h"
#include "YousifErrorHandling.h"
#include"WindosErrorMacros.h"
#include "Keyboard.h"
#include "Mouse.h"
#include"Graphics.h"
#include<optional>
#include<memory>



class Window
{
	/*************************** Windows Error Handling ******************************************/
public:
	class Errors : public YousifError
	{
	public:
		Errors(int Line, const char* File, HRESULT HR) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		static std::string TransError(HRESULT HR) noexcept;
		HRESULT GetError() const noexcept;
		std::string GetErrorStr()const noexcept;
	private:
		HRESULT HR;
	};

	/**********************************************************************************************/

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

	static std::optional<int> ProcMsg();
	
	Graphics& Gfx();

	Keyboard KBD;
	Mouse MUS;
private:
	static LRESULT WINAPI HandleMsgSetup(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	static LRESULT WINAPI HandleMsgRe(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT HandleMsg(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
private:
	int X;
	int Y;
	std::unique_ptr<Graphics> pGfx;
	HWND HWnd;
};


