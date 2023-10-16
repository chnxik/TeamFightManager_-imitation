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
		ChampSelectSlot(const std::wstring& Key);
		virtual ~ChampSelectSlot();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void SetState(eState state);
		virtual void RegistRespawnPool();
		virtual void SetActive();
		virtual void SetPaused();

		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();
		virtual void MouseOn();

		virtual void MouseUp();
		virtual void MouseAway();

	public:
		void RegistChamp(eChamp champ);
		void RegistWindowUI(BanPickWindow* BPWin);

		void SlotAnimationSet(eChamp champ);

		void StateClear();

    private:
		BanPickWindow* OwnerWindowUI;

		Champ* mRegistedChamp;
		Text* mChampName;

		UIObject* mChampTex;
		UIObject* mSelectLine;
		UIObject* mPickedOutline;
		UIObject* mPickedBg;

		bool bBanned;
		bool bSelected;
        
    };
}