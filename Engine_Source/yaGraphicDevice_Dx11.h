#pragma once
#include "660Engine.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace ya::graphics
{
	class GraphicDevice_Dx11
	{
	public:
		GraphicDevice_Dx11();
		~GraphicDevice_Dx11();

		bool CreateSwapChain(const DXGI_SWAP_CHAIN_DESC* desc, HWND hWnd); // 스왑체인 생성
		bool CreateBuffer(ID3D11Buffer** buffer, D3D11_BUFFER_DESC* desc, D3D11_SUBRESOURCE_DATA* data); // 정점버퍼 생성
		bool CreateShader(); // 쉐이더 생성

		bool CreateTexture(const D3D11_TEXTURE2D_DESC* desc, void* data); // 텍스쳐 생성 함수

		void BindViewPort(D3D11_VIEWPORT* viewPort); // 뷰포트 바인드 함수

		void Draw(); // 그리기 함수

	private:
		// 실제 그래픽카드 하드웨어 객체
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;

		// dx11에서 직접적으로 디바이스객체 접근하지않고
		// 이 객체를 이용하여 명령을 내린다.
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

		// 최종적으로 그려질 텍스쳐(도화지)
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;

		// 렌더타겟에 직접 접근하지 않고 렌더타겟뷰를 통해서 접근한다.
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

		// 깊이 버퍼
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;

		// 깊이버퍼에 접근할 수 있는 뷰
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		// 더블버퍼링 작업을 진행해주는 swapChain
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		D3D11_VIEWPORT mViewPort;
	};

	// Device 객체를 바로 불러오는 함수.
	inline GraphicDevice_Dx11*& GetDevice()
	{
		static GraphicDevice_Dx11* device = nullptr;
		return device;
	}
}