#pragma once
#include "sszResource.h"
#include "sszGraphics.h"

namespace ssz::graphics
{
	class ComputeShader : public Resource
	{
	public:
		ComputeShader();
		virtual ~ComputeShader();

		bool Create(const std::wstring& name, const std::string& methodName);
		virtual HRESULT Load(const std::wstring& path) { return S_FALSE; }

	private:
		Microsoft::WRL::ComPtr<ID3DBlob> mCSBlob;
		Microsoft::WRL::ComPtr<ID3D11ComputeShader> mCS;
	};
}