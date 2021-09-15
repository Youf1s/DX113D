#include "TransformCBuf.h"


TransformCBuf::TransformCBuf(Graphics& Gfx, const DrawIt& Parent)
	:
	VCBuf(Gfx),
	Parent(Parent)
{
};

void TransformCBuf::BindItt(Graphics& Gfx)
{
	VCBuf.Update(Gfx,
		DirectX::XMMatrixTranspose(Parent.GetTransform() * Gfx.GetProjection()));
	VCBuf.BindItt(Gfx);
};
