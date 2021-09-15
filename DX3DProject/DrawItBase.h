#pragma once
#include "DrawIt.h"
#include "IndexBuffer.h"

template<class T>
class DrawItBase : public DrawIt
{
public:
	bool IsStaticInitialized() const noexcept
	{
		return !staticBinds.empty();
	}
	void AddStaticBind(std::unique_ptr<BindIt> bind) noexcept
	{
		
		staticBinds.push_back(std::move(bind));
	}
	void AddStaticIndexBuffer(std::unique_ptr<IndexBuffer> ibuf) noexcept
	{
	
		pIndexBuf = ibuf.get();
		staticBinds.push_back(std::move(ibuf));
	}
	void SetIndexFromStatic() noexcept
	{
	
		for (const auto& b : staticBinds)
		{
			if (const auto p = dynamic_cast<IndexBuffer*>(b.get()))
			{
				pIndexBuf = p;
				return;
			}
		}
		
	}
private:
	const std::vector<std::unique_ptr<BindIt>>& GetStaticBinds() const noexcept override
	{
		return staticBinds;
	}
private:
	static std::vector<std::unique_ptr<BindIt>> staticBinds;
};

template<class T>
std::vector<std::unique_ptr<BindIt>> DrawItBase<T>::staticBinds;