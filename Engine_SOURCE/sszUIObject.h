#pragma once
#include "sszGameObject.h"

namespace ssz
{
	class UIObject : public GameObject
	{
	public:
		UIObject();
		UIObject(const std::wstring& Key);
		virtual ~UIObject();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void SetState(eState state);
		virtual void RegistRespawnPool();
		virtual void SetActive();
		virtual void SetPaused();

		bool IsMouseOn() { return bMouseOn; }
		bool IsLbtnDown() { return bLbtnDown; }

		UIObject* GetParentUI() { return mParentUI; }
		const std::vector<UIObject*>& GetChildUI() { return mChildUI; }

		bool IsUIOpen() { return bOpen; }
		void UIOpen() { bOpen = true; }
		void UIClose() { bOpen = false; }

		virtual void MouseLbtnDown();
		virtual void MouseLbtnUp();
		virtual void MouseLbtnClicked();
		virtual void MouseOn();

		virtual void MouseUp() {}
		virtual void MouseAway() {}

	private:
		void MouseOnCheck();

	private:

		UIObject* mParentUI;
		std::vector<UIObject*> mChildUI;

		bool bLbtnDown;
		bool bMouseOn;

		bool bOpen;

		void AddChildUI(UIObject* pChildUI)
		{
			pChildUI->mParentUI = this;
			mChildUI.push_back(pChildUI);
			Transform* Parenttr = GetComponent<Transform>();
			pChildUI->GetComponent<Transform>()->SetParent(Parenttr);
		}

		void AddParentUI(UIObject* pParentUI)
		{
			mParentUI = pParentUI;
			pParentUI->mChildUI.push_back(this);
			Transform* Parenttr = pParentUI->GetComponent<Transform>();
			GetComponent<Transform>()->SetParent(Parenttr);
		}
	protected:
		const std::wstring mUIKey;

		friend class PanelUI;
	};
}