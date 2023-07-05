#include "sszMasking.h"
#include "sszApplication.h"
#include "sszRenderer.h"
#include "sszConstantBuffer.h"
#include "sszCamera.h"

extern ssz::Application application;

namespace ssz
{
	using namespace ssz::graphics;
	Masking::Masking()
		: Component(eComponentType::Panel)
	{
	}

	Masking::~Masking()
	{
	}

	void Masking::Initialize()
	{
	}

	void Masking::Update()
	{
	}

	void Masking::LateUpdate()
	{
	}

	void Masking::Render()
	{
	}

	void Masking::BindConstantBuffer()
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = (float)(rect.right - rect.left);
		float height = (float)(rect.bottom - rect.top);

		Viewport viewport;
		viewport.width = width;
		viewport.height = height;

		viewport.x = (float)rect.left;
		viewport.y = (float)rect.top;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		Vector3 LT(0.0f, 0.0f, 0.0f);
		Vector3 RB(0.5f, 0.5f, 0.0f);

		LT = viewport.Project(LT, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		RB = viewport.Project(RB, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		renderer::MaskingCB paCB;
		paCB.Left = LT.x;
		paCB.Top = RB.y;
		paCB.Right = RB.x;
		paCB.Bottom = LT.y;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Masking];
		cb->SetData(&paCB);
		cb->Bind(eShaderStage::PS);
	}
}