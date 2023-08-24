#include "sszText.h"
#include "sszFontWrapper.h"
#include "sszCamera.h"

#include "sszApplication.h"

#include "sszGameObject.h"
#include "sszTransform.h"

extern ssz::Application application;

namespace ssz
{
	Text::Text()
		: Component(eComponentType::Text)
		, mString{}
		, mFontPos{}
		, mOffsetPos{}
		, mFontSize(100.f)
		, mFontColor(0)
	{
	}

	Text::~Text()
	{
	}

	void Text::Initialize()
	{
	}

	void Text::Update()
	{
	}

	void Text::LateUpdate()
	{
		GameObject* Owner = GetOwner();
		Transform* Ts = Owner->GetComponent<Transform>();

		mFontPos = Ts->GetWorldPosition();
		mFontPos.y *= -1.f;

		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = (float)(rect.right - rect.left);
		float height = (float)(rect.bottom - rect.top);
		
		mFontPos.x += width / 2.f + mOffsetPos.x;
		mFontPos.y += height / 2.f + mOffsetPos.y;
	}

	void Text::Render()
	{
		if (mString.size() != 0)
		{
			FontWrapper::DrawFont(mString.c_str(), mFontPos.x, mFontPos.y, mFontSize, mFontColor);
		}
	}

	void Text::SetFontColor(UINT R, UINT G, UINT B, UINT A)
	{
		mFontColor = FONT_RGBA(R, G, B, A);
	}
}