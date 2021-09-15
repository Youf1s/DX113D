#include "DrawIt.h"
#include"IndexBuffer.h"


void DrawIt::DrawItt(Graphics& Gfx) const
{
	for (auto& b : Binds)
	{
		b->BindItt(Gfx);
	}
	for (auto& b : GetStaticBinds())
	{
		b->BindItt(Gfx);
	}
	Gfx.DrawIndex(pIndexBuf->GetCount());
	
}

void DrawIt::AddBind(std::unique_ptr<BindIt> Bind)
{
	
	Binds.push_back(std::move(Bind));
}

void DrawIt::AddIndexBuf(std::unique_ptr<class IndexBuffer> IBuf)
{
	
	pIndexBuf = IBuf.get();
	Binds.push_back(std::move(IBuf));
}
