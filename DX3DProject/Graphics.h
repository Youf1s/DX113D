#pragma once
#include"YousifWin.h"
#include<d3d11.h>
#include"YousifErrorHandling.h"
#include<vector>
#include<DirectXMath.h>
#include <memory>
#include<d3dcompiler.h>
#include<wrl.h>
class Graphics
{
	friend class BindIt;


	/************************ For Errors in Graphics **********************************/
public:
	class Errors : public YousifError
	{
		using YousifError::YousifError;
	};
	class HrErrors : public Errors
	{
	public:
		HrErrors(int line, const char* file, HRESULT hr) noexcept;
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		HRESULT GetErrorCode() const noexcept;

		std::string GetErrorDescription() const noexcept;
		static std::string TransError(HRESULT HR) noexcept;
	private:
		HRESULT hr;
	};
	class DeviceRemovedException : public HrErrors
	{
		using HrErrors::HrErrors;
	public:
		const char* GetType() const noexcept override;
	};
	/*********************************************************************************/



public:
	Graphics(HWND HWnd);
	~Graphics() = default;
	Graphics(const Graphics&) = delete;
	Graphics& operator=(const Graphics&) = delete;
	void DrawIndex(UINT Count);
	void SetProjection(DirectX::FXMMATRIX Proj);
	DirectX::XMMATRIX GetProjection() const;
	void ClearBuffer(float red, float green, float blue, float alpha);
	void EndFrame();
	
private:
	DirectX::XMMATRIX projection;


	Microsoft::WRL::ComPtr<IDXGISwapChain>				pSwapChain;
	Microsoft::WRL::ComPtr<ID3D11Device>				pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>			pContext;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>		pTarget;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>		pDSV;
};

