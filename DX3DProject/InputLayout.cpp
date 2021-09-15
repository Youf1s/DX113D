#include "InputLayout.h"
#include"GraphicErrorMacros.h"

InputLayout::InputLayout(Graphics& Gfx, const std::vector<D3D11_INPUT_ELEMENT_DESC>& Desc, ID3DBlob* pVBlob)
{
	HRESULT hr;
	YOUSIF_ERROR_GFX(GetDevice(Gfx)->CreateInputLayout(Desc.data(), (UINT)Desc.size(),
		pVBlob->GetBufferPointer(), pVBlob->GetBufferSize(), &pInputLayout));
}

void InputLayout::BindItt(Graphics& Gfx)
{
	GetContext(Gfx)->IASetInputLayout(pInputLayout.Get());
}
