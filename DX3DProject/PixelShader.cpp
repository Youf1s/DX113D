#include "PixelShader.h"
#include"GraphicErrorMacros.h"
PixelShader::PixelShader(Graphics& Gfx, const std::wstring& Path)
{
	HRESULT hr;
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	YOUSIF_ERROR_GFX(D3DReadFileToBlob(Path.c_str(), &pBlob));
	YOUSIF_ERROR_GFX(GetDevice(Gfx)->CreatePixelShader(pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(), nullptr, &pPixelShader));

}

void PixelShader::BindItt(Graphics& Gfx)
{
	GetContext(Gfx)->PSSetShader(pPixelShader.Get(), nullptr, 0u);
}
