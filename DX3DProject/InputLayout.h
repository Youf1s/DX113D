#pragma once
#include"BindIt.h"
class InputLayout : public BindIt
{
public:
	InputLayout(Graphics& Gfx,const std::vector<D3D11_INPUT_ELEMENT_DESC>& Desc,
		ID3DBlob* pVBlob);
	void BindItt(Graphics& Gfx) override;

protected:
	Microsoft::WRL::ComPtr<ID3D11InputLayout> pInputLayout;
};

