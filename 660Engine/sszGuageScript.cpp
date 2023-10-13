#include "sszGuageScript.h"

#include "CommonHeader.h"

namespace ssz
{
	GuageScript::GuageScript()
		: mType(eGuageType::END)
		, mMax(0.f)
		, mValue(nullptr)
		, fRatio(0.f)
	{
	}

	GuageScript::~GuageScript()
	{
	}

	void GuageScript::Update()
	{
	}

	void GuageScript::LateUpdate()
	{
		switch (mType)
		{
		case ssz::GuageScript::INT:
		{
			fRatio = (float)*((int*)mValue) / mMax;
			break;
		}
		case ssz::GuageScript::FLOAT:
		{
			fRatio = *((float*)mValue) / mMax;
			break;
		}
		};
	}

	void GuageScript::Binds()
	{
		// AnimationCB
		renderer::GuageCB data = {};

		data.GuageRatio = fRatio;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Guage];
		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
	}
	
	void GuageScript::SetValue(int Max, int* ValueAddress)
	{
		mType = eGuageType::INT;
		mMax = (float)Max;
		mValue = ValueAddress;
	}
	
	void GuageScript::SetValue(float Max, float* ValueAddress)
	{
		mType = eGuageType::FLOAT;
		mMax = Max;
		mValue = ValueAddress;
	}
}