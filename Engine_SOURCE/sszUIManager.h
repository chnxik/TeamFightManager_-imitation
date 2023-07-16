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
		// �ֻ��� �θ�UI ���� �ڽ� UI���� �����Ͽ� ���� �켱������ ���� UI Ž��
		static UIObject* GetPriorityUI(UIObject* pParentUI);

	private:
		static UIObject* mFocusedUI;
		static UIObject* mPriorityUI;

	};
}