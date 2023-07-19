#pragma once
#include "sszUIComponent.h"

namespace ssz
{
	class PanelUI : public UIComponent
	{
	public:
		enum ePanelType
		{
			None,
			AddPraentPos,
		};

		PanelUI();
		virtual ~PanelUI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();

		virtual void BindConstantBuffer() {};

		virtual void MouseLbtnDown() {};
		virtual void MouseLbtnUp() {};
		virtual void MouseLbtnClicked() {};
		virtual void MouseOn() {};

		void AddChildUI(UIObject* pChildUI) { GetOwnerUI()->AddChildUI(pChildUI); }
		void AddParentUI(UIObject* pParentUI) { GetOwnerUI()->AddChildUI(pParentUI); }

		void SetPanelType(ePanelType etype) { mtype = etype; }
		ePanelType GetPanerType() { return mtype; }

	private:
		ePanelType mtype;
	};
}