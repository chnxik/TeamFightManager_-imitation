#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class Champ;
	class PlayerCardSlot;
	class Text;

    class ChampDataSlot :
        public UIObject
    {
	public:
		ChampDataSlot(const std::wstring& key);
		virtual ~ChampDataSlot();

		virtual void LateUpdate() override;
		virtual void Initialize() override;

		void RegistChamp(Champ* champ) { mRegistedChamp = champ; }
		void RegistPlayerCardSlot(PlayerCardSlot* Slot);

	private:
		PlayerCardSlot* mOwnerSlot;
		Champ* mRegistedChamp;

		Text* mSlotTitle;	// Á¤º¸
		Text* mScoreTypeK;	// K
		Text* mScoreTypeD;	// D
		Text* mScoreTypeA;	// A

		Text* mScoreK;	// K
		Text* mScoreD;	// D
		Text* mScoreA;	// A

		Text* mDeal;
		Text* mDamaged;
		Text* mHeal;
    };
}