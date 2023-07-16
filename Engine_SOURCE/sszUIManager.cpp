#include "sszUIManager.h"
#include "sszUIObject.h"

#include "sszInput.h"

#include "sszSceneManager.h"
#include "sszScene.h"
#include "sszLayer.h"

#include "sszGameObject.h"

namespace ssz
{
	UIObject* UIManager::mFocusedUI = nullptr;
	UIObject* UIManager::mPriorityUI = nullptr;

	void UIManager::LateUpdate()
	{
		bool bLbtnDown = ssz::Input::GetKeyDown(eKeyCode::LBUTTON);
		bool bLbtnUp = ssz::Input::GetKeyUp(eKeyCode::LBUTTON);

		// ���� �� ����
		Scene* ActiveScene = SceneManager::GetActiveScene();

		// UI Layer ��������
		const std::vector<GameObject*>& vecUI = ActiveScene->GetLayer(eLayerType::UI).GetGameObjects();

		for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
		{
			mPriorityUI = GetPriorityUI((UIObject*)vecUI[i]); // ���� UI�� �켱���� UI�� �ִ��� Ȯ���Ѵ�.

			if (nullptr == mPriorityUI) // �켱���� UI�� ���� ��� ���� UI �˻縦 ����
				continue;

			// ���콺�� �̺�Ʈ ȣ��
			mPriorityUI->MouseOn();

			// �̹� update�� Lbtn�� ���ȴ�.
			if (bLbtnDown)
			{
				// LbtnDoww �̺�Ʈ ȣ��
				mPriorityUI->MouseLbtnDown();
				break;

				// ���� ������ z���� ���� �����Ǿ� ���⼭ �������� �ʴ´�.
			}

			// �̹� update�� Lbtn�� ������.
			else if (bLbtnUp)
			{
				// ������ �������� �ִ�.
				if (mPriorityUI->IsLbtnDown())
				{
					// Ŭ�� �̺�Ʈ ȣ��
					mPriorityUI->MouseLbtnClicked();
					mPriorityUI->MouseLbtnUp();
				}
			}
		}
	}

	UIObject* UIManager::GetPriorityUI(UIObject* pParentUI)
	{
		bool bLbtnReleased = ssz::Input::GetKeyUp(eKeyCode::LBUTTON);

		UIObject* pPriorityUI = nullptr;

		static std::queue<UIObject*> _queue;
		_queue.push(pParentUI); // ���ڷ� ���� �θ�UI�� ���� ���� �ִ´�.

		while (!_queue.empty()) // queue�� ��ü�� ���� ���������� �ݺ�
		{
			UIObject* pUI = _queue.front(); // Queue�� ���� �տ� �ִ� UI�� �����´�.
			_queue.pop(); // ������ UI�� Queue���� �����.

			const std::vector<UIObject*>& ChildUI = pUI->GetChildUI(); // ������ UI�� �ڽ�UI���� �����´�.

			for (size_t i = 0; i < ChildUI.size(); ++i)
			{
				_queue.push(ChildUI[i]); // ���ʴ�� Queue�� ����ִ´�.
			}

			// UI�� ���� Ȯ��
			if (pUI->IsMouseOn())
			{
				// �켱���� UI�� ����������, ������ �켱������ ���� �ٸ� UI�� ���� ���.
				// ���� UI�� LbtnDown ���¸� �����Ѵ�.
				if (bLbtnReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
				{
					pPriorityUI->MouseLbtnUp();
				}

				// �켱���� UI�� ����
				pPriorityUI = pUI;
			}

			// �켱����UI�� ���� �ȵ� UI�� ���콺 ���������� �߻��ϸ� LbtnUp ���·� ���´�.
			else if (bLbtnReleased)
			{
				pUI->MouseLbtnUp();
			}
		}

		return pPriorityUI;
	}

	void UIManager::CloseUI(UIObject* pParentUI)
	{
	}

	void UIManager::OpenUI(UIObject* pParentUI)
	{
	}
}