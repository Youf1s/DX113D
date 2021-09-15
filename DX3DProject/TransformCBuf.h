#pragma once
#include"ConstBuf.h"
#include"DrawIt.h"
#include <DirectXMath.h>

class TransformCBuf : public BindIt
{
public:
	TransformCBuf(Graphics& Gfx, const DrawIt& Parent);
	void BindItt(Graphics& Gfx) override;

private:
	VertexConsttBuf<DirectX::XMMATRIX> VCBuf;

	const DrawIt& Parent;
};

