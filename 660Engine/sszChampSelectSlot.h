#pragma once
#include "sszUIObject.h"
#include "GameEnums.h"

namespace ssz
{
	class Champ;
	class Text;
	class BanPickWindow;

    class ChampSelectSlot : public UIObject
    {
    public:
		enum class ePhase
		{
			BanPhase,
			SelectPhase,
		};
		
		ChampSelectSlot(const std::wstring& Key);
		virtual ~ChampSelectSlot();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void SetState(eState state);
		virtual void RegistRespawnPool();

		virtual void MouseLbtnClicked();

		virtual void MouseUp();
		virtual void MouseAway();

	public:
		void RegistChamp(eChamp champ);
		void RegistWindowUI(BanPickWindow* BPWin);

		void AiPick();

		void SlotAnimationSet(eChamp champ);

		void ChampSelected();
		void StateClear();

		void BanPhase() { mPhase = ePhase::BanPhase; }
		void SelectPhase() { mPhase = ePhase::SelectPhase; }

		void SetPlayerTurn() { bPlayerTurn = true; }
		void SetEnemyTurn() { bPlayerTurn = false; }

		bool IsBanned() { return bBanned; }
		bool IsSelected() { return bSelected; }

    private:
		ePhase mPhase;
		BanPickWindow* OwnerWindowUI;

		Champ* mRegistedChamp;
		Text* mChampName;

		UIObject* mChampTex;
		UIObject* mSelectLine;
		UIObject* mPickedOutline;
		UIObject* mPickedBg;

		bool bPlayerTurn;
		bool bBanned;
		bool bSelected;
        
    };
}