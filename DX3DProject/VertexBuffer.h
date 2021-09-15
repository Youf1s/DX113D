#pragma once
#include"BindIt.h"


class VertexBuffer : public BindIt
{
public:
	template<class VB>
	VertexBuffer(Graphics& Gfx,const std::vector<VB>& Vertices)
		:
		Stride(sizeof(VB))
	{
		D3D11_BUFFER_DESC bd = {};
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.ByteWidth = UINT(sizeof(VB) * Vertices.size());
		bd.CPUAccessFlags = 0u;
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.MiscFlags = 0u;
		bd.StructureByteStride = sizeof(VB);
		D3D11_SUBRESOURCE_DATA sd = {};
		sd.pSysMem = Vertices.data();
		
		GetDevice(Gfx)->CreateBuffer(&bd, &sd, &pVertexBuffer);

	}


	void BindItt(Graphics& Gfx) override;
	

protected:
	UINT Stride;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pVertexBuffer;
};

