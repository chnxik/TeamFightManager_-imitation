#pragma once
#include "sszTestScript.h"
#include "CommonObjHeader.h"

namespace ssz
{
	class CheckStop : public Condition // 정지 컨디션
	{
	public:
		CheckStop(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			if (Input::GetKey(eKeyCode::SPACE))
			{
				return SetStatus(NS_SUCCESS);
			}

			return SetStatus(NS_FAILURE);
		}
	};

	class DetectedCursor100 : public Condition // 커서 탐지 컨디션
	{
	public:
		DetectedCursor100(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Transform>()->GetWorldPosition();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>()->GetWorldPosition();

			float dist = sqrt(
				(CsrPos.x - OwnerPos.x) * (CsrPos.x - OwnerPos.x) +
				(CsrPos.y - OwnerPos.y) * (CsrPos.y - OwnerPos.y));

			if (dist < 100.f)
			{
				return SetStatus(NS_SUCCESS);
			}

			//Anim->PlayAnimation(L"archer_move", true);

			return 	SetStatus(NS_FAILURE);
		}
	};

	

	class CheckLeft : public Condition // 왼쪽방향 컨디션
	{
	public:
		CheckLeft(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}

		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			if (mtr->IsLeft())
				return SetStatus(NS_SUCCESS);
			else
				return SetStatus(NS_FAILURE);
		}
	};

	class CheckRight : public Condition // 오른쪽 방향 컨디션
	{
	public:
		CheckRight(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}
		
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			if (mtr->IsRight())
				return SetStatus(NS_SUCCESS);
			else
				return SetStatus(NS_FAILURE);
		}
	};

	class CheckCsrifLeft : public Condition
	{
	public:
		CheckCsrifLeft(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}

		Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Transform>()->GetWorldPosition();
		Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>()->GetWorldPosition();

		virtual eNodeStatus Run() override
		{
			if (CsrPos.x - OwnerPos.x >= 0)
				return SetStatus(NS_SUCCESS);

			return SetStatus(NS_FAILURE);
		}
	};

	class CheckCsrifRight : public Condition
	{
	public:
		CheckCsrifRight(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}

		Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Transform>()->GetWorldPosition();
		Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>()->GetWorldPosition();

		virtual eNodeStatus Run() override
		{
			if (CsrPos.x - OwnerPos.x <= 0)
				return SetStatus(NS_SUCCESS);

			return SetStatus(NS_FAILURE);
		}
	};

	class CheckLeftDist : public Condition
	{
	public:
		CheckLeftDist(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}

		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			Vector3 pos = mtr->GetPosition();

			if (-100.f > pos.x)
				return SetStatus(NS_SUCCESS);

			return SetStatus(NS_FAILURE);
		}
	};

	class CheckRightDist : public Condition
	{
	public:
		CheckRightDist(std::shared_ptr<AIBB> pAIBB) : Condition(pAIBB) {}
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();


		virtual eNodeStatus Run() override
		{
			Vector3 pos = mtr->GetPosition();

			if (100.f < pos.x)
				return SetStatus(NS_SUCCESS);
			
			return SetStatus(NS_FAILURE);
		}
	};

	class TurnLeft : public Action
	{
	public:
		TurnLeft(std::shared_ptr<AIBB> pAIBB) : Action(pAIBB) {}
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			mtr->SetLeft();
			return SetStatus(NS_SUCCESS);
		}
	};

	class TurnRight : public Action
	{
	public:
		TurnRight(std::shared_ptr<AIBB> pAIBB) : Action(pAIBB) {}
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			mtr->SetRight();
			return SetStatus(NS_SUCCESS);
		}
	};

	class MoveLeft : public Action
	{
	public:
		MoveLeft(std::shared_ptr<AIBB> pAIBB) : Action(pAIBB) {}
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();
		Vector3 pos = mtr->GetPosition();

		virtual eNodeStatus Run() override
		{
			pos.x -= 100.f * (float)Time::DeltaTime();
			mtr->SetPosition(pos);

			return SetStatus(NS_SUCCESS);
		}
	};

	class MoveRight : public Action
	{
	public:
		MoveRight(std::shared_ptr<AIBB> pAIBB) : Action(pAIBB) {}
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();
		Vector3 pos = mtr->GetPosition();

		virtual eNodeStatus Run() override
		{
			pos.x += 100.f * (float)Time::DeltaTime();
			mtr->SetPosition(pos);

			return SetStatus(NS_SUCCESS);
		}
	};

	class PlayIdleAnim : public Action
	{
	public:
		PlayIdleAnim(std::shared_ptr<AIBB> pAIBB) : Action(pAIBB) {}
		Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

		virtual eNodeStatus Run() override
		{
			anim->PlayAnimation(L"archer_idle", true);
			return SetStatus(NS_SUCCESS);
		}
	};

	class PlayMoveAnim : public Action
	{
	public:
		PlayMoveAnim(std::shared_ptr<AIBB> pAIBB) : Action(pAIBB) {}
		Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

		virtual eNodeStatus Run() override
		{
			anim->PlayAnimation(L"archer_move", true);
			return SetStatus(NS_SUCCESS);
		}
	};

	class PlayAttackAnim : public Action
	{
	public:
		PlayAttackAnim(std::shared_ptr<AIBB> pAIBB) : Action(pAIBB) {}
		Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

		virtual eNodeStatus Run() override
		{
			anim->PlayAnimation(L"archer_attack", true);
			return SetStatus(NS_SUCCESS);
		}
	};
}