#include "sszCircle.h"
#include "sszRenderer.h"

namespace ssz
{
	Circle::Circle()
		: mRadius(0.0f)
		, mPos{}
		, mColor{}
	{
	}

	Circle::~Circle()
	{
	}

	void Circle::Initialize()
	{
	}
	
	void Circle::Update()
	{
	}
	
	void Circle::LateUpdate()
	{
	}
	
	void Circle::Render()
	{
		renderer::GetConstantBuffer(eCBType::Transform)->SetData(&mPos);
		renderer::GetConstantBuffer(eCBType::Transform)->Bind(eShaderStage::VS);

		renderer::GetConstantBuffer(eCBType::Color)->SetData(&mColor);
		renderer::GetConstantBuffer(eCBType::Color)->Bind(eShaderStage::PS);

		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		graphics::GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}

	void Circle::CreateCicle(Vector4 Pos, Vector4 Color)
	{
		SetPos(Pos);
		SetColor(Color.x, Color.y, Color.z);
	}
}