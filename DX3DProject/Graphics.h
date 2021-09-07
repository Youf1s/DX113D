#pragma once
#include"YousifWin.h"
#include<d3d11.h>
#include<stdexcept>
class Graphics
{
public:
	Graphics(HWND HWnd);
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	~Graphics();
	void EndFrame();
	void ClearBuffer(float red, float green, float blue, float alpha);
private:
	IDXGISwapChain* pSwapChain = nullptr;
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr ;
	ID3D11RenderTargetView* pTarget = nullptr;
};

