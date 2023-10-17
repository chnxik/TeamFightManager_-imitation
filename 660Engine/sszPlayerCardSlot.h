#pragma once
#include "sszUIObject.h"
#include "sszTexture.h"
#include "GameEnums.h"

namespace ssz
{
	class Champ;
	class Pilot;
	class Text;

	class PlayerCardSlot : public UIObject
	{
	public:
		PlayerCardSlot(const std::wstring& key);
		virtual ~PlayerCardSlot();

		virtual void Initialize() override;

		void RegistPilot(Pilot* pilot);
		void RegistChamp(Champ* champ);
		Pilot* GetPilot() { return mRegistedPilot; }
		
		void SelectDone();
		Pilot* CurSelectedSlot();

		eTeamColor GetTeamColor() { return mTeamColor; }

		void SetSlotNumb(UINT i) { mSlotNumb = i; }
		UINT GetSlotNumb() { return mSlotNumb; }

		void SetRed();
		void SetBlue();

	private:
		Pilot* mRegistedPilot;
		Champ* mRegistedChamp;

		UINT mSlotNumb;

		Text* mPilotName;
		Text* mCharacter;

		UIObject* mAtkIcon;
		UIObject* mDefIcon;

		std::shared_ptr<Texture> vecCardTex[(UINT)eTeamColor::End][(UINT)eSlotState::End];
		
		eTeamColor mTeamColor;
		
		bool bSelect;
		UIObject* mAvatarFace;
	};
}