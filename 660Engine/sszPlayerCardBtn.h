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

		virtual void Initialize() override;

		ButtonUI* GetBtnComponent() { return mBtnComp; }
		void SetRed();
		void SetBlue();

	private:
		ButtonUI* mBtnComp;
		std::shared_ptr<Texture> vecCardTex[(UINT)eTeamColor::End][(UINT)ButtonUI::eBtnState::End];
	};
}