#pragma once
#include "sszTestScript.h"
#include "CommonObjHeader.h"

namespace ssz
{
	// Condition Node
	class Con_IsStopBtnPush : public Condition_Node // ���� �����
	{
	public:
		virtual eNodeStatus Run() override
		{
			if (Input::GetKey(eKeyCode::SPACE))
			{
				return NS_SUCCESS;
			}

			return NS_FAILURE;
		}
	};
	class Con_CollisionCsr : public Condition_Node // Ŀ�� Ž�� �����
	{
	public:
		virtual eNodeStatus Run() override
		{
			Collider2D* CsrCol = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Collider2D>();
			Collider2D* OwnerCol = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Collider2D>();

			if (CollisionManager::IsCollision(OwnerCol,CsrCol))
			{
				return NS_SUCCESS;
			}

			return 	NS_FAILURE;
		}
	};
	class Con_DetectCsr_300px : public Condition_Node // Ŀ�� Ž�� �����
	{
	public:
		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Collider2D>()->GetColliderPos();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Collider2D>()->GetColliderPos();

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
	class Con_IsLeft : public Condition_Node // ���ʹ��� �����
	{
	public:
		virtual eNodeStatus Run() override
		{
			Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

			if (mtr->IsLeft())
				return NS_SUCCESS;
			else
				return NS_FAILURE;
		}
	};
	class Con_IsRight : public Condition_Node // ������ ���� �����
	{
	public:
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
		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Collider2D>()->GetColliderPos();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Collider2D>()->GetColliderPos();
			
			if (CsrPos.x <= OwnerPos.x)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};
	class Con_CsrOntheRight : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			Vector3 CsrPos = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Collider2D>()->GetColliderPos();
			Vector3 OwnerPos = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Collider2D>()->GetColliderPos();

			if (CsrPos.x > OwnerPos.x)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};
	class Con_IsOver_LeftArea : public Condition_Node
	{
	public:
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
		virtual eNodeStatus Run() override
		{
			Animator* anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

			anim->PlayAnimation(L"archer_dead", false);
			return NS_SUCCESS;
		}
	};

	class Act_TestRunning : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			static int repeat = 0;

			repeat++;

			if (repeat < 2)
				return NS_RUNNING;
			else
				return NS_SUCCESS;
		}
	};
}