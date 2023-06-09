#include "sszConstantBuffer.h"
#include "sszGraphicDevice_Dx11.h"

namespace ssz::graphics
{
	ssz::graphics::ConstantBuffer::ConstantBuffer(const eCBType type)
		: GpuBuffer()
		, mType(type)
	{
	}

	ssz::graphics::ConstantBuffer::~ConstantBuffer()
	{
	}

	bool ssz::graphics::ConstantBuffer::Create(size_t size)
	{
		desc.ByteWidth = (UINT)size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ssz::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return false;
	}

	void ssz::graphics::ConstantBuffer::SetData(void* data)
	{
		ssz::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}

	void ssz::graphics::ConstantBuffer::Bind(eShaderStage stage)
	{
		ssz::graphics::GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
	}
}