#include "VertexBuffer.h"

void VertexBuffer::BindItt(Graphics& Gfx)
{
	const UINT Offset = 0u;
	GetContext(Gfx)->IASetVertexBuffers(0u, 1u, pVertexBuffer.GetAddressOf(),
		&Stride, &Offset);
}
