#pragma once
#include"Graphics.h"

class BindIt;

class DrawIt
{
	template<class T>
	friend class DrawItBase;
public:
	DrawIt() = default;
	virtual ~DrawIt() = default;
	DrawIt(const DrawIt&) = delete;
	virtual DirectX::XMMATRIX GetTransform() const = 0;
	void DrawItt(Graphics& Gfx) const ;
	virtual void Update(float DA) = 0;
	void AddBind(std::unique_ptr<BindIt> Bind);
	void AddIndexBuf(std::unique_ptr<class IndexBuffer> IBuf);

private:

	virtual const std::vector<std::unique_ptr<BindIt>>& GetStaticBinds() const noexcept = 0;


	const IndexBuffer* pIndexBuf = nullptr;
	std::vector<std::unique_ptr<BindIt>> Binds;


};

