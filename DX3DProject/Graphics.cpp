#include "Graphics.h"
#include<sstream>
#include"GraphicErrorMacros.h"



#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")
Graphics::Graphics(HWND HWnd)
{
	/****************Swap Chain Desc***********************/
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
	/*******************************************/

	//For Error Macro
	HRESULT hr;


	/********************* Creating SwapchainAndDevice ****************************/
	YOUSIF_ERROR_GFX(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION, &SD, &pSwapChain, &pDevice, nullptr, &pContext));
	/*******************************************/





	/*********************Geting Back Buffer ****************************/
	Microsoft::WRL::ComPtr<ID3D11Resource> pResource;
	YOUSIF_ERROR_GFX(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pResource));
	YOUSIF_ERROR_GFX(pDevice->CreateRenderTargetView(pResource.Get(), nullptr, &pTarget));
	/*****************************************/





	/************************Creating Depth State And Binding It************************************/
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	YOUSIF_ERROR_GFX(pDevice->CreateDepthStencilState(&dsDesc, &pDSState));
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);
	/**************************/



	/***************************** Texture For Depth And Binding It*********************************/
	Microsoft::WRL::ComPtr<ID3D11Texture2D> pDepthStencil;
	D3D11_TEXTURE2D_DESC descDepth = {};
	descDepth.Width = 1920u;
	descDepth.Height = 1080u;
	descDepth.MipLevels = 1u;
	descDepth.ArraySize = 1u;
	descDepth.Format = DXGI_FORMAT_D32_FLOAT;
	descDepth.SampleDesc.Count = 1u;
	descDepth.SampleDesc.Quality = 0u;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	YOUSIF_ERROR_GFX(pDevice->CreateTexture2D(&descDepth, nullptr, &pDepthStencil));
	/******************************************/

	





	/******************************Desc Depth And Binding It*******************************************/
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	YOUSIF_ERROR_GFX(pDevice->CreateDepthStencilView(
		pDepthStencil.Get(), &descDSV, &pDSV));
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());
	/**************************************/



	/**************************View Port Desc And Binding It************************************/
	D3D11_VIEWPORT vip;
	vip.Width = 1920.0f;
	vip.Height = 1080.0f;
	vip.MinDepth = 0.0f;
	vip.MaxDepth = 1.0f;
	vip.TopLeftX = 0.0f;
	vip.TopLeftY = 0.0f;
	pContext->RSSetViewports(1u, &vip);
	/************************************************/
}



void Graphics::EndFrame()
{
	
	pSwapChain->Present(1u, 0u);

}


void Graphics::DrawIndex(UINT Count)
{
	pContext->DrawIndexed(Count, 0u, 0u);
}

void Graphics::SetProjection(DirectX::FXMMATRIX Proj)
{
	projection = Proj;
}

DirectX::XMMATRIX Graphics::GetProjection() const
{
	return projection;
}

void Graphics::ClearBuffer(float red, float green, float blue, float alpha)
{
	const float Color[4] = { red,green,blue,alpha };
	pContext->ClearRenderTargetView(pTarget.Get(), Color);

	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}





/******************************Error Handling Stuff**********************************************/

Graphics::HrErrors::HrErrors(int line, const char* file, HRESULT hr) noexcept
	:
	Errors(line, file),
	hr(hr)
{}

const char* Graphics::HrErrors::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Error Code] 0x" << std::hex << std::uppercase << GetErrorCode()
		<< std::dec << " (" << (unsigned long)GetErrorCode() << ")" << std::endl
		<< "[Error String] " << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl <<
		GetOrSt();
	WtBuf = oss.str();
	return WtBuf.c_str();
}

const char* Graphics::HrErrors::GetType() const noexcept
{
	return "Yousif Graphics Error";
}

HRESULT Graphics::HrErrors::GetErrorCode() const noexcept
{
	return hr;
}



std::string Graphics::HrErrors::GetErrorDescription() const noexcept
{
	return TransError(hr);
}


const char* Graphics::DeviceRemovedException::GetType() const noexcept
{
	return "Yousif Graphics Error [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}

std::string Graphics::HrErrors::TransError(HRESULT HR) noexcept
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