#include "IndexBuffer.h"
#include"GraphicErrorMacros.h"

IndexBuffer::IndexBuffer(Graphics& Gfx, const std::vector<unsigned short>& Indices)
	:
	Count((UINT)Indices.size())
{
	D3D11_BUFFER_DESC ibd = {};

	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = UINT(Count * sizeof(unsigned short));
	ibd.CPUAccessFlags = 0u;
	ibd.Usage = D3D11_USAGE_DEFAULT;
	ibd.MiscFlags = 0u;
	ibd.StructureByteStride = sizeof(unsigned short);
	D3D11_SUBRESOURCE_DATA isd = {};
	isd.pSysMem = Indices.data();
	HRESULT hr;
	YOUSIF_ERROR_GFX(GetDevice(Gfx)->CreateBuffer(&ibd, &isd, &pIndexBuf));

}

void IndexBuffer::BindItt(Graphics& Gfx)
{
	GetContext(Gfx)->IASetIndexBuffer(pIndexBuf.Get(), DXGI_FORMAT_R16_UINT, 0u);
}

UINT IndexBuffer::GetCount() const
{
	return Count;
}
