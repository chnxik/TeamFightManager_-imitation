#pragma once
#include "sszTestScript.h"
#include "CommonObjHeader.h"

namespace ssz
{
	// Condition Node
	class Con_IsStopBtnPush : public Condition_Node // 정지 컨디션
	{
	public:
		Con_IsStopBtnPush(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			if (Input::GetKey(eKeyCode::SPACE))
			{
				return NS_SUCCESS;
			}

			return NS_FAILURE;
		}
	};
	class Con_DetectCsr_50px : public Condition_Node // 커서 탐지 컨디션
	{
	public:
		Con_DetectCsr_50px(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Transform>()->GetWorldPosition();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>()->GetWorldPosition();

			float dist = sqrt(
				(CsrPos.x - OwnerPos.x) * (CsrPos.x - OwnerPos.x) +
				(CsrPos.y - OwnerPos.y) * (CsrPos.y - OwnerPos.y));

			if (dist < 50.f)
			{
				return NS_SUCCESS;
			}

			return 	NS_FAILURE;
		}
	};
	class Con_DetectCsr_300px : public Condition_Node // 커서 탐지 컨디션
	{
	public:
		Con_DetectCsr_300px(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Transform>()->GetWorldPosition();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>()->GetWorldPosition();

			float dist = sqrt(
				(CsrPos.x - OwnerPos.x) * (CsrPos.x - OwnerPos.x) +
				(CsrPos.y - OwnerPos.y) * (CsrPos.y - OwnerPos.y));

			if (dist < 300.f)
			{
				return NS_SUCCESS;
			}

			return 	NS_FAILURE;
		}
	};
	class Con_IsLeft : public Condition_Node // 왼쪽방향 컨디션
	{
	public:
		Con_IsLeft(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}


		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

			if (mtr->IsLeft())
				return NS_SUCCESS;
			else
				return NS_FAILURE;
		}
	};
	class Con_IsRight : public Condition_Node // 오른쪽 방향 컨디션
	{
	public:
		Con_IsRight(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}
		

		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

			if (mtr->IsRight())
				return NS_SUCCESS;
			else
				return NS_FAILURE;
		}
	};
	class Con_CsrOntheLeft : public Condition_Node
	{
	public:
		Con_CsrOntheLeft(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}


		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Transform>()->GetWorldPosition();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>()->GetWorldPosition();
			
			if (CsrPos.x <= OwnerPos.x)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};
	class Con_CsrOntheRight : public Condition_Node
	{
	public:
		Con_CsrOntheRight(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}


		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Transform>()->GetWorldPosition();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>()->GetWorldPosition();

			if (CsrPos.x > OwnerPos.x)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};
	class Con_IsOver_LeftArea : public Condition_Node
	{
	public:
		Con_IsOver_LeftArea(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}


		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

			Vector3 pos = mtr->GetPosition();

			if (-100.f > pos.x)
			{
				return NS_SUCCESS;
			}

			return NS_FAILURE;
		}
	};
	class Con_IsOver_RightArea : public Condition_Node
	{
	public:
		Con_IsOver_RightArea(std::shared_ptr<AIBB> pAIBB) : Condition_Node(pAIBB) {}


		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

			Vector3 pos = mtr->GetPosition();

			if (100.f < pos.x)
			{
				return NS_SUCCESS;
			}
			
			return NS_FAILURE;
		}
	};
	
	// Action Node
	class Act_TurnLeft : public Action_Node
	{
	public:
		Act_TurnLeft(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

			mtr->SetLeft();
			return NS_SUCCESS;
		}
	};
	class Act_TurnRight : public Action_Node
	{
	public:
		Act_TurnRight(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

			mtr->SetRight();
			return NS_SUCCESS;
		}
	};
	class Act_MoveLeft : public Action_Node
	{
	public:
		Act_MoveLeft(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();
			Vector3 pos = mtr->GetPosition();

			pos.x -= 100.f * (float)Time::DeltaTime();
			mtr->SetPosition(pos);

			return NS_SUCCESS;
		}
	};
	class Act_MoveRight : public Action_Node
	{
	public:
		Act_MoveRight(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();
			Vector3 pos = mtr->GetPosition();

			pos.x += 100.f * (float)Time::DeltaTime();
			mtr->SetPosition(pos);

			return NS_SUCCESS;
		}
	};
	class Act_PlayAnim_Idle : public Action_Node
	{
	public:
		Act_PlayAnim_Idle(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

			anim->PlayAnimation(L"archer_idle", true);
			return NS_SUCCESS;
		}
	};
	class Act_PlayAnim_Move : public Action_Node
	{
	public:
		Act_PlayAnim_Move(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

			anim->PlayAnimation(L"archer_move", true);
			return NS_SUCCESS;
		}
	};
	class Act_PlayAnim_Attack : public Action_Node
	{
	public:
		Act_PlayAnim_Attack(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

			anim->PlayAnimation(L"archer_attack", true);
			return NS_SUCCESS;
		}
	};
	class Act_PlayAnim_Dead : public Action_Node
	{
	public:
		Act_PlayAnim_Dead(std::shared_ptr<AIBB> pAIBB) : Action_Node(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

			anim->PlayAnimation(L"archer_dead", false);
			return NS_SUCCESS;
		}
	};
}