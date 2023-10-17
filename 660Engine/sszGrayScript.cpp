#include "sszGrayScript.h"
#include "sszRenderer.h"
#include "sszConstantBuffer.h"

namespace ssz
{
	GrayScript::GrayScript()
		: useGray(false)
		, useAlpha(false)
		, grayRatio(0.5f)
		, AlphaRatio(1.f)
	{
	}

	GrayScript::~GrayScript()
	{
	}
	
	void GrayScript::Binds()
	{
		if (!useGray)
			return;

		renderer::ColorFXCB data = {};

		data.useGray = useGray;
		data.useAlpha = useAlpha;
		data.GrayRatio = grayRatio;
		data.AlphaRatio = AlphaRatio;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::ColorFX];
		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
	}

	void GrayScript::BindsClear()
	{
		renderer::ColorFXCB data = {};

		data.useGray = false;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::ColorFX];
		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
	}
}