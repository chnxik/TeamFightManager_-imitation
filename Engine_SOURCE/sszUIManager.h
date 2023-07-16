#pragma once


namespace ssz
{
	class UIObject;
	
	class UIManager
	{
	public:
		static void LateUpdate();

		static void CloseUI(UIObject* pParentUI);
		static void OpenUI(UIObject* pParentUI);

	private:
		// 최상위 부모UI 부터 자식 UI까지 포함하여 가자 우선순위가 높은 UI 탐색
		static UIObject* GetPriorityUI(UIObject* pParentUI);

	private:
		static UIObject* mFocusedUI;
		static UIObject* mPriorityUI;

	};
}