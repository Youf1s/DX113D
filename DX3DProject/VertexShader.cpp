#include "VertexShader.h"
#include"GraphicErrorMacros.h"
VertexShader::VertexShader(Graphics& Gfx, const std::wstring& Path) 
{
	
	D3DReadFileToBlob(Path.c_str(), &pBlob);
	 GetDevice(Gfx)->CreateVertexShader(pBlob->GetBufferPointer(),
		pBlob->GetBufferSize(), nullptr, &pVertexShader);
	
}
void VertexShader::BindItt(Graphics& Gfx)
{
	GetContext(Gfx)->VSSetShader(pVertexShader.Get(), nullptr, 0u);
}

ID3DBlob* VertexShader::GetpBlob()
{
	return pBlob.Get();
}
