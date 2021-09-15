#pragma once
#include"BindIt.h"
class VertexShader : public BindIt
{
public:
	VertexShader(Graphics& Gfx,const std::wstring& Path);
	void BindItt(Graphics& Gfx) override;
	ID3DBlob* GetpBlob();

protected:
	Microsoft::WRL::ComPtr<ID3DBlob> pBlob;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> pVertexShader;
};

