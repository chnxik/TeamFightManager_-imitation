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

		// 현재 씬 접근
		Scene* ActiveScene = SceneManager::GetActiveScene();

		// UI Layer 가져오기
		const std::vector<GameObject*>& vecUI = ActiveScene->GetLayer(eLayerType::UI).GetGameObjects();

		for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
		{
			mPriorityUI = GetPriorityUI((UIObject*)vecUI[i]); // 현재 UI에 우선순위 UI가 있는지 확인한다.

			if (nullptr == mPriorityUI) // 우선순위 UI가 없는 경우 다음 UI 검사를 진행
				continue;

			// 마우스온 이벤트 호출
			mPriorityUI->MouseOn();

			// 이번 update에 Lbtn이 눌렸다.
			if (bLbtnDown)
			{
				// LbtnDoww 이벤트 호출
				mPriorityUI->MouseLbtnDown();
				break;

				// 렌더 순서는 z값에 의해 결정되어 여기서 관여하지 않는다.
			}

			// 이번 update에 Lbtn이 떼졌다.
			else if (bLbtnUp)
			{
				// 이전에 눌린적이 있다.
				if (mPriorityUI->IsLbtnDown())
				{
					// 클릭 이벤트 호출
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
		_queue.push(pParentUI); // 인자로 들어온 부모UI를 가장 먼저 넣는다.

		while (!_queue.empty()) // queue에 객체가 남지 않을때까지 반복
		{
			UIObject* pUI = _queue.front(); // Queue의 가장 앞에 있는 UI를 가져온다.
			_queue.pop(); // 가져온 UI를 Queue에서 지운다.

			const std::vector<UIObject*>& ChildUI = pUI->GetChildUI(); // 가져온 UI의 자식UI들을 가져온다.

			for (size_t i = 0; i < ChildUI.size(); ++i)
			{
				_queue.push(ChildUI[i]); // 차례대로 Queue에 집어넣는다.
			}

			// UI의 상태 확인
			if (pUI->IsMouseOn())
			{
				// 우선순위 UI로 지정됐지만, 더높은 우선순위를 가진 다른 UI가 나온 경우.
				// 기존 UI의 LbtnDown 상태를 갱신한다.
				if (bLbtnReleased && nullptr != pPriorityUI && pPriorityUI->IsLbtnDown())
				{
					pPriorityUI->MouseLbtnUp();
				}

				// 우선순위 UI로 지정
				pPriorityUI = pUI;
			}

			// 우선순위UI로 지정 안된 UI는 마우스 해제조건이 발생하면 LbtnUp 상태로 놓는다.
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