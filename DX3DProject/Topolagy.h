#pragma once
#include"BindIt.h"
class Topolagy : public BindIt
{
public:
	Topolagy(D3D11_PRIMITIVE_TOPOLOGY Type);
	void BindItt(Graphics& Gfx) override;

protected:
	D3D11_PRIMITIVE_TOPOLOGY Type;
};

