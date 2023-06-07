#include "yaConstantBuffer.h"
#include "yaGraphicDevice_Dx11.h"

namespace ya::graphics
{
	ya::graphics::ConstantBuffer::ConstantBuffer(const eCBType type)
		: GpuBuffer()
		, mType(type)
	{
	}

	ya::graphics::ConstantBuffer::~ConstantBuffer()
	{
	}

	bool ya::graphics::ConstantBuffer::Create(size_t size)
	{
		desc.ByteWidth = (UINT)size;
		desc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		desc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		ya::graphics::GetDevice()->CreateBuffer(buffer.GetAddressOf(), &desc, nullptr);

		return false;
	}

	void ya::graphics::ConstantBuffer::SetData(void* data)
	{
		ya::graphics::GetDevice()->SetConstantBuffer(buffer.Get(), data, desc.ByteWidth);
	}

	void ya::graphics::ConstantBuffer::Bind(eShaderStage stage)
	{
		ya::graphics::GetDevice()->BindConstantBuffer(stage, mType, buffer.Get());
	}
}