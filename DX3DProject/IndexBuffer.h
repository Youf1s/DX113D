#pragma once
#include"BindIt.h"

class IndexBuffer : public BindIt
{
public:
	IndexBuffer(Graphics& Gfx, const std::vector<unsigned short>& Indices);
	void BindItt(Graphics& Gfx) override;
	UINT GetCount() const;
	
protected:
	UINT Count;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pIndexBuf;
};

