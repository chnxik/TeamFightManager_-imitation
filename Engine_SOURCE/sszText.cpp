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
		, mFont{}
		, mString{}
		, mFontPos{}
		, mOffsetPos{}
		, mFontSize(100.f)
		, mFontColor(0)
		, mFlags(0)
	{
		mFontColor = FONT_RGBA(255, 255, 255, 255);
	}

	Text::~Text()
	{
	}

	void Text::Initialize()
	{
		SetFont(L"Silver");
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
		mFontPos.y += height / 2.f - mOffsetPos.y;
	}

	void Text::Render()
	{
		if (mString.size() != 0)
		{
			FontWrapper::DrawFont(mString.c_str(), mFont.c_str(), mFontPos.x, mFontPos.y, mFontSize, mFontColor, mFlags);
		}
	}

	void Text::TextInit(const std::wstring& Font, Vector3 OffsetPos, float FontSize, UINT FontColor, UINT flags)
	{
		mFont = Font;
		mOffsetPos = OffsetPos;
		mFontSize = FontSize;
		mFontColor = FontColor;
		mFlags = flags;
	}

	void Text::SetFontColor(UINT R, UINT G, UINT B, UINT A)
	{
		mFontColor = FONT_RGBA(R, G, B, A);
	}
}