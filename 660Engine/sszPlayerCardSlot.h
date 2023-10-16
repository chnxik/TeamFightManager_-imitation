#pragma once
#include "sszUIObject.h"
#include "sszTexture.h"
#include "GameEnums.h"

namespace ssz
{
	class Pilot;
	class Text;

	class PlayerCardSlot : public UIObject
	{
	public:
		PlayerCardSlot(const std::wstring& key);
		virtual ~PlayerCardSlot();

		virtual void Initialize() override;

		void RegistPilot(Pilot* pilot);

		void SetRed();
		void SetBlue();

	private:
		Pilot* mRegistedPilot;

		Text* mPilotName;
		Text* mCharacter;

		UIObject* mAtkIcon;
		UIObject* mDefIcon;

		std::shared_ptr<Texture> vecCardTex[(UINT)eTeamColor::End][(UINT)eSlotState::End];
		bool bSelect;
		UIObject* mAvatarFace;
	};
}