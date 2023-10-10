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
		
		mFonts[(UINT)Text::eFonts::Galmuri9] = L"Galmuri9";
		mFonts[(UINT)Text::eFonts::Galmuri11] = L"Galmuri11";
		mFonts[(UINT)Text::eFonts::Galmuri14] = L"Galmuri14";
		mFonts[(UINT)Text::eFonts::Silver] = L"Silver";

		SetFont(Text::eFonts::Silver);
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
		mFontPos.z += mFontPos.z + mOffsetPos.z;
	}

	void Text::Render()
	{
		if (mString.size() != 0)
		{
			FontWrapper::DrawFont(mString.c_str(), mFont.c_str(), mFontPos.x, mFontPos.y, mFontSize, mFontColor, mFlags);
		}
	}

	void Text::TextInit(Text::eFonts FontType, Vector3 OffsetPos, float FontSize, UINT FontColor, UINT flags)
	{
		mFont = mFonts[(UINT)FontType];
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