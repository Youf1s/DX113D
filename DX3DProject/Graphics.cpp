#include "Graphics.h"

#pragma comment(lib,"d3d11.lib")

Graphics::Graphics(HWND HWnd)
{
	DXGI_SWAP_CHAIN_DESC SD = {};
	SD.BufferDesc.Width = 0;
	SD.BufferDesc.Height = 0;
	SD.BufferDesc.RefreshRate.Denominator = 0;
	SD.BufferDesc.RefreshRate.Numerator = 0;
	SD.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	SD.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	SD.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	SD.SampleDesc.Count = 1;
	SD.SampleDesc.Quality = 0;
	SD.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	SD.BufferCount = 1;
	SD.OutputWindow = HWnd;
	SD.Windowed = TRUE;
	SD.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	SD.Flags = 0;

	D3D11CreateDeviceAndSwapChain(nullptr,D3D_DRIVER_TYPE_HARDWARE,nullptr, 0,
		nullptr,0, D3D11_SDK_VERSION,&SD,&pSwapChain,&pDevice,nullptr,&pContext);

	ID3D11Resource* pResource = nullptr;
	pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), reinterpret_cast<void**>(&pResource));
	pDevice->CreateRenderTargetView(pResource, nullptr, &pTarget);
	pResource->Release();

}

Graphics::~Graphics()
{
	if (pTarget != nullptr)
	{
		pTarget->Release();
	}
	if (pContext != nullptr)
	{
		pContext->Release();
	}
	
	if (pSwapChain != nullptr)
	{
		pSwapChain->Release();
	}
	
	if (pDevice != nullptr)
	{
		pDevice->Release();
	}
}

void Graphics::EndFrame()
{
	if (pSwapChain != nullptr)
	{
		pSwapChain->Present(1u, 0u);
	}
	else
	{
		throw std::runtime_error("pSwapChaine is NULL in Graphics.h\n");
	}
	
	
}

void Graphics::ClearBuffer(float red, float green, float blue, float alpha)
{
	const float Color[4] = { red,green,blue,alpha };
	pContext->ClearRenderTargetView(pTarget, Color);
}

