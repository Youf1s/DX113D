#include "Topolagy.h"

Topolagy::Topolagy(D3D11_PRIMITIVE_TOPOLOGY Type)
	:
	Type(Type)
{}

void Topolagy::BindItt(Graphics& Gfx)
{
	GetContext(Gfx)->IASetPrimitiveTopology(Type);
}
