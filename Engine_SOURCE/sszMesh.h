#pragma once
#include "sszResource.h"
#include "sszGraphicDevice_Dx11.h"

namespace ssz
{
	using namespace graphics;

	class Mesh : public Resource
	{
	public:
		Mesh();
		~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

		bool CreateVertexBuffer(void* data, UINT Count);
		bool CreateIndexBuffer(void* data, UINT Count);

		void BindBuffer(); // Buffer 파이프라인에 묶어준다.
		void Render();

		UINT GetIndexCount() { return mIndexCount; }

	private:
		Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer; // 정점 버퍼
		Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer; // 인덱스 버퍼

		D3D11_BUFFER_DESC mVBDesc;	// 정점 버퍼 설정값
		D3D11_BUFFER_DESC mIBDesc;	// 인덱스 버퍼 설정값

		UINT mIndexCount;	// 인덱스 버퍼 갯수
	};
}