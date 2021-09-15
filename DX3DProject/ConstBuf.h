#pragma once
#include"BindIt.h"


template<typename CB>
class ConstBuf : public BindIt
{
public:
	void Update(Graphics& Gfx, const CB& ConstsBufs)
	{
		D3D11_MAPPED_SUBRESOURCE MSR;
		GetContext(Gfx)->Map(pConstBuf.Get(), 0u,
			D3D11_MAP_WRITE_DISCARD, 0u,&MSR);

		memcpy(MSR.pData, &ConstsBufs, sizeof(ConstsBufs));

		GetContext(Gfx)->Unmap(pConstBuf.Get(), 0u);
	}
	ConstBuf(Graphics& Gfx, const CB& ConstsBufs)
	{

		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(ConstsBufs);
		cbd.StructureByteStride = 0u;

		D3D11_SUBRESOURCE_DATA csd = {};
		csd.pSysMem = &ConstsBufs;
		GetDevice(Gfx)->CreateBuffer(&cbd, &csd, &pConstBuf);
	}

	ConstBuf(Graphics& Gfx)
	{

		D3D11_BUFFER_DESC cbd;
		cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		cbd.Usage = D3D11_USAGE_DYNAMIC;
		cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
		cbd.MiscFlags = 0u;
		cbd.ByteWidth = sizeof(CB);
		cbd.StructureByteStride = 0u;
		GetDevice(Gfx)->CreateBuffer(&cbd, nullptr, &pConstBuf);
	}


protected:
	Microsoft::WRL::ComPtr<ID3D11Buffer> pConstBuf;
private:
	
};


template<typename CB>
class VertexConsttBuf : public ConstBuf<CB>
{
	using ConstBuf<CB>::pConstBuf;
	using BindIt::GetContext;
public:
	using ConstBuf<CB>::ConstBuf;
	void BindItt(Graphics& Gfx)  override
	{
		GetContext(Gfx)->VSSetConstantBuffers(0u, 1u, pConstBuf.GetAddressOf());
	}
};



template<typename CB>
class PixelConstantBuf : public ConstBuf<CB>
{
	using ConstBuf<CB>::pConstBuf;
	using BindIt::GetContext;
public:
	using ConstBuf<CB>::ConstBuf;
	void BindItt(Graphics& Gfx)  override
	{
		GetContext(Gfx)->PSSetConstantBuffers(0u, 1u, pConstBuf.GetAddressOf());
	}
};


