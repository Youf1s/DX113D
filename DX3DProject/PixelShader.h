#pragma once
#include"BindIt.h"
class PixelShader : public BindIt
{
public:
	PixelShader(Graphics& Gfx, const std::wstring& Path);
	void BindItt(Graphics& Gfx) override;
protected:
	Microsoft::WRL::ComPtr<ID3D11PixelShader> pPixelShader;
};

