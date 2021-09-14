#include "DxErrorInfo.h"
#include "Window.h"
#include<dxgidebug.h>
#include<memory>

#pragma comment(lib, "dxguid.lib")

#define YOUSIF_NOIN_ERROR_GFX(Hrs) if( FAILED( hr = (Hrs) ) ) throw Graphics::HrErrors( __LINE__,__FILE__,hr )

DxErrorInfo::DxErrorInfo()
{
	typedef HRESULT(WINAPI* DXGIGetDebugInterface)(REFIID, void**);

	const auto hModDxgiDebug = LoadLibraryEx("dxgidebug.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);

	if (hModDxgiDebug == nullptr)
	{
		throw YOUSIF_LAST_ERROR();
	}

	const auto DxgiGetDebugInterface = reinterpret_cast<DXGIGetDebugInterface>(
		reinterpret_cast<void*>(GetProcAddress(hModDxgiDebug, "DXGIGetDebugInterface"))
		);
	if (DxgiGetDebugInterface == nullptr)
	{
		throw YOUSIF_LAST_ERROR();
	}

	HRESULT hr;
	//YOUSIF_NOIN_ERROR_GFX(DxgiGetDebugInterface(__uuidof(pDxginfo), reinterpret_cast<void**>(&pDxgiInfoQueue)));
}



void DxErrorInfo::Set() noexcept
{
	Next = pDxginfo->GetNumStoredMessages(DXGI_DEBUG_ALL);
}

std::vector<std::string> DxErrorInfo::GetMessages() const
{
	std::vector<std::string> messages;
	const auto end = pDxginfo->GetNumStoredMessages(DXGI_DEBUG_ALL);
	for (auto i = Next; i < end; i++)
	{
		HRESULT hr;
		SIZE_T messageLength;
		// get the size of message i in bytes
		YOUSIF_NOIN_ERROR_GFX(pDxginfo->GetMessage(DXGI_DEBUG_ALL, i, nullptr, &messageLength));
		// allocate memory for message
		auto bytes = std::make_unique<byte[]>(messageLength);
		auto pMessage = reinterpret_cast<DXGI_INFO_QUEUE_MESSAGE*>(bytes.get());
		// get the message and push its description into the vector
		YOUSIF_NOIN_ERROR_GFX(pDxginfo->GetMessage(DXGI_DEBUG_ALL, i, pMessage, &messageLength));
		messages.emplace_back(pMessage->pDescription);
	}
	return messages;
}
