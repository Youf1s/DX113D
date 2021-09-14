#include "Graphics.h"
#include<d3dcompiler.h>
#include<sstream>
#include<DXGItype.h>
#include<DirectXMath.h>





#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"D3DCompiler.lib")

#define YOUSIF_ERROR_GFX(HRs)if(FAILED(hr =(HRs) ))throw Graphics::HrErrors(__LINE__,__FILE__,hr)
#define YOUSIF_DEVICE_ERROR_GFX(hr) Graphics::HrErrors(__LINE__,__FILE__,(hr))

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

	
	HRESULT hr;

	YOUSIF_ERROR_GFX(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, D3D11_CREATE_DEVICE_DEBUG,
		nullptr, 0, D3D11_SDK_VERSION, &SD, &pSwapChain, &pDevice, nullptr, &pContext));
	

	Microsoft::WRL::ComPtr<ID3D11Resource> pResource;
	YOUSIF_ERROR_GFX(pSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), &pResource));
	YOUSIF_ERROR_GFX( pDevice->CreateRenderTargetView(pResource.Get(), nullptr, &pTarget));

	D3D11_DEPTH_STENCIL_DESC dsDesc = {};
	dsDesc.DepthEnable = TRUE;
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> pDSState;
	YOUSIF_ERROR_GFX(pDevice->CreateDepthStencilState(&dsDesc, &pDSState));

	// bind depth state
	pContext->OMSetDepthStencilState(pDSState.Get(), 1u);

	// create depth stensil texture
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

	// create view of depth stensil texture
	D3D11_DEPTH_STENCIL_VIEW_DESC descDSV = {};
	descDSV.Format = DXGI_FORMAT_D32_FLOAT;
	descDSV.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	descDSV.Texture2D.MipSlice = 0u;
	YOUSIF_ERROR_GFX(pDevice->CreateDepthStencilView(
		pDepthStencil.Get(), &descDSV, &pDSV
	));

	// bind depth stensil view to OM
	pContext->OMSetRenderTargets(1u, pTarget.GetAddressOf(), pDSV.Get());

}

void Graphics::EndFrame()
{
	HRESULT hr;
	if (FAILED(hr = pSwapChain->Present(1u, 0u)))
	{
		if (hr == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw YOUSIF_DEVICE_ERROR_GFX(pDevice->GetDeviceRemovedReason());
		}
		else
		{
			YOUSIF_ERROR_GFX(hr);
		}
	}
	
}

void Graphics::ClearBuffer(float red, float green, float blue, float alpha)
{
	const float Color[4] = { red,green,blue,alpha };
	pContext->ClearRenderTargetView(pTarget.Get(), Color);

	pContext->ClearDepthStencilView(pDSV.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0u);
}

void Graphics::DrawTestTri( float angle,float x,float y ,float z)
{
	
	struct Vertex
	{
		struct 
		{
			float x;
			float y;
			float z;
		} pos;
		struct 
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} color;
		
	};

	Vertex verices[] =
	{
		{ -1.0f,-1.0f,-1.0f,255,200,0,1},
		{ 1.0f,-1.0f,-1.0f,255,0,0,1},
		{ -1.0f,1.0f,-1.0f,255,190,0,1},
		{ 1.0f,1.0f,-1.0f,255,0,0,1},
		{ -1.0f,-1.0f,1.0f,255,0,0,1},
		{ 1.0f,-1.0f,1.0f,255,0,0,1},
		{ -1.0f,1.0f,1.0f,255,0,0,1},
		{ 1.0f,1.0f,1.0f,255,0,0,1},
	};
	HRESULT hr;

	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
	D3D11_BUFFER_DESC bd = {};
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.ByteWidth = sizeof(verices);
	bd.CPUAccessFlags = 0u;
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.MiscFlags = 0u;
	bd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA sd = {};
	sd.pSysMem = verices;
	YOUSIF_ERROR_GFX(pDevice->CreateBuffer(&bd, &sd, &pVertexBuffer));

	
	const UINT stride = sizeof(Vertex);
	const UINT offset = 0u;
	pContext->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(), &stride, &offset);
	
	const unsigned short indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
	};


	struct ConstantBuf2
	{
		struct 
		{
			float r;
			float g;
			float b;
			float a;
		}FaceColor[6];
	};


	ConstantBuf2 cb2 =
	{
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer2;
	D3D11_BUFFER_DESC cbd2 = {};
	cbd2.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	cbd2.ByteWidth = sizeof(cb2);
	cbd2.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd2.Usage = D3D11_USAGE_DYNAMIC;
	cbd2.MiscFlags = 0u;
	cbd2.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd2 = {};
	csd2.pSysMem = &cb2;

	YOUSIF_ERROR_GFX(pDevice->CreateBuffer(&cbd2, &csd2, &pConstantBuffer2));

	pContext->PSSetConstantBuffers(0u, 1u, pConstantBuffer2.GetAddressOf());


	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuffer;
	D3D11_BUFFER_DESC ibd = {};

	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = sizeof(verices);
	ibd.CPUAccessFlags = 0u;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.MiscFlags = 0u;
	ibd.StructureByteStride = sizeof(Vertex);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = indices;

	YOUSIF_ERROR_GFX(pDevice->CreateBuffer(&ibd, &isd, &pIndexBuffer));

	pContext->IASetIndexBuffer(pIndexBuffer.Get(),DXGI_FORMAT_R16_UINT,0u);

	struct ConstantBuf
	{
			DirectX::XMMATRIX transformation;
	};


	ConstantBuf cb =
	{
		{
			DirectX::XMMatrixTranspose(DirectX::XMMatrixRotationZ(angle) * DirectX::XMMatrixRotationY(angle)* DirectX::XMMatrixTranslation(x,y,z) * DirectX::XMMatrixPerspectiveLH(1.0f,9.0f / 16.0f,0.5f,16.0f))
		}
	};
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstantBuffer;
	D3D11_BUFFER_DESC cbd = {};
	cbd.BindFlags = D3D10_BIND_CONSTANT_BUFFER;
	cbd.ByteWidth = sizeof(cb);
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.MiscFlags = 0u;
	cbd.StructureByteStride = 0u;
	D3D11_SUBRESOURCE_DATA csd = {};
	csd.pSysMem = &cb;

	YOUSIF_ERROR_GFX(pDevice->CreateBuffer(&cbd, &csd, &pConstantBuffer));

	pContext->VSSetConstantBuffers(0u, 1u, pConstantBuffer.GetAddressOf());

	Microsoft::WRL::ComPtr<ID3DBlob> pBlop;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
	YOUSIF_ERROR_GFX(D3DReadFileToBlob(L"PixelShader.cso", &pBlop));
	YOUSIF_ERROR_GFX(pDevice->CreatePixelShader(pBlop->GetBufferPointer(), pBlop->GetBufferSize(), nullptr, &pPixelShader));
	pContext->PSSetShader(pPixelShader.Get(), nullptr, 0u);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
	YOUSIF_ERROR_GFX( D3DReadFileToBlob(L"VertexShader.cso",&pBlop));
	YOUSIF_ERROR_GFX(pDevice->CreateVertexShader(pBlop->GetBufferPointer(), pBlop->GetBufferSize(), nullptr, &pVertexShader));
	pContext->VSSetShader(pVertexShader.Get(), nullptr, 0u);


	

	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;

	const D3D11_INPUT_ELEMENT_DESC ide[] =
	{
		{"Position",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	YOUSIF_ERROR_GFX(pDevice->CreateInputLayout(ide, (UINT)std::size(ide),
		pBlop->GetBufferPointer(), pBlop->GetBufferSize(), &pInputLayout));

	pContext->IASetInputLayout(pInputLayout.Get());


	

	pContext->IASetPrimitiveTopology(D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT vp;
	vp.Width = 1920;
	vp.Height = 1080;
	vp.MinDepth = 0;
	vp.MaxDepth = 1;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	pContext->RSSetViewports(1u, &vp);

	pContext->DrawIndexed((UINT)std::size(indices),0u,0u);

}






/////////////// Error Handling ////////////////


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