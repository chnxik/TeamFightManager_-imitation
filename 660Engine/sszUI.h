#pragma once
#include "..\Engine_SOURCE\sszGameObject.h"

namespace ssz::UI
{
	class UI : public GameObject
	{
	public:
		UI();
		virtual ~UI();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

	private:
		UI* mParentUI;
		std::vector<UI*> mChildUIs;

		bool mbLbtnDown;
		bool mbCsrOn;
	};
}