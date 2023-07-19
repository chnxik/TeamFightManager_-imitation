#pragma once
#include "sszUIObject.h"
#include "sszButtonUI.h"
#include "sszTexture.h"

namespace ssz
{
	class PlayerCardBtn : public UIObject
	{
	public:
		PlayerCardBtn(const std::wstring& key);
		virtual ~PlayerCardBtn();

		ButtonUI* GetBtnComponent() { return mBtnComp; }
		void SetRed();
		void SetBlue();

	private:
		enum eTeamColor
		{
			Red,
			Blue
		};

		enum eBtnState
		{
			Idle,
			On,
			Down,
		};

		ButtonUI* mBtnComp;
		std::shared_ptr<Texture> vecCardTex[2][3];
	};
}