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
		
		// �����ִ� vecUI�� ���� �տ��ִ�(z���� ����) UI�� ��Ŀ�� UI�� �Ѵ�.
		mFocusedUI = nullptr;

		
		// Focused UI
		for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
		{
			if (((UIObject*)vecUI[i])->IsMouseOn()
				&& vecUI[i]->IsActive())
			{
				if (mFocusedUI == nullptr)
				{
					mFocusedUI = (UIObject*)vecUI[i];
					continue;
				}

				if (mFocusedUI->IsMouseOn())
				{
					float PrevFocusZ = mFocusedUI->GetComponent<Transform>()->GetWorldPosition().z;
					float NewFocuseZ = vecUI[i]->GetComponent<Transform>()->GetWorldPosition().z;

					if (PrevFocusZ > NewFocuseZ)
						mFocusedUI = (UIObject*)vecUI[i];
				}
				else
				{
					mFocusedUI = (UIObject*)vecUI[i];
				}
			}
		}

		for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
		{
			mPriorityUI = GetPriorityUI((UIObject*)vecUI[i]); // ���� UI�� �켱���� UI�� �ִ��� Ȯ���Ѵ�.


			if (nullptr == mPriorityUI) // �켱���� UI�� ���� ��� ���� UI �˻縦 ����
				continue;

			if (mFocusedUI != vecUI[i])	// �켱���� UI�� ��Ŀ�̵� UI�� �ƴѰ��
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

		UIObject* ppUI = pParentUI;
		
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
		static std::queue<UIObject*> _Closequeue;
		_Closequeue.push(pParentUI);

		while (!_Closequeue.empty())
		{
			UIObject* pUI = _Closequeue.front();
			_Closequeue.pop();

			const std::vector<UIObject*>& vecChild = pUI->GetChildUI();
			for (size_t i = 0; i < vecChild.size(); ++i)
			{
				_Closequeue.push(vecChild[i]);
			}

			pUI->SetPaused();
		}
	}

	void UIManager::OpenUI(UIObject* pParentUI)
	{
		static std::queue<UIObject*> _Openqueue;
		_Openqueue.push(pParentUI);

		while (!_Openqueue.empty())
		{
			UIObject* pUI = _Openqueue.front();
			_Openqueue.pop();

			const std::vector<UIObject*>& vecChild = pUI->GetChildUI();
			for (size_t i = 0; i < vecChild.size(); ++i)
			{
				_Openqueue.push(vecChild[i]);
			}

			pUI->SetActive();
		}
	}
}