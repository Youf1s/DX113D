#pragma once
#include"Graphics.h"
class BindIt
{
public:
	virtual void BindItt(Graphics& Gfx) = 0;
	~BindIt() = default;

protected:
	static ID3D11Device* GetDevice(Graphics& Gfx);
	static ID3D11DeviceContext* GetContext(Graphics& Gfx);
};

