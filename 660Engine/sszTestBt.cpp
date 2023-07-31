#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	// Condition Node
	class Con_IsStopBtnPush : public Condition_Node // 정지 컨디션
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
	class Con_CollisionCsr : public Condition_Node // 커서 충돌 컨디션
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Collider2D* CsrCol = mAIBB->FindData<GameObject>(L"Cursor")->GetComponent<Collider2D>();
			Collider2D* OwnerCol = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Collider2D>();

			if (CollisionManager::IsCollision(OwnerCol,CsrCol))
			{
				return NS_SUCCESS;
			}

			return 	NS_FAILURE;
		}
	};

	class Con_CollisionOtehrChamp : public Condition_Node // 다른 챔프 충돌 컨디션
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* Owner = mAIBB->FindData<Champ>(*ChampName);

			Collider2D* OwnerCol = Owner->FindColObjsCol(L"AttackArea");
			Collider2D* TargetCol = nullptr;

			Champ* Target = Owner->GetEnemys().begin()->second;
			TargetCol = Target->GetComponent<Collider2D>();

			if (CollisionManager::IsCollision(TargetCol, OwnerCol))
				return NS_SUCCESS;


			return NS_FAILURE;
		}
	};

	class Con_MustBack : public Condition_Node // 커서 탐지 컨디션
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* Owner = mAIBB->FindData<Champ>(*ChampName);

			Vector3 TargetPos = Owner->GetEnemys().begin()->second->GetComponent<Collider2D>()->GetColliderPos();
			Vector3 OwnerPos = Owner->GetComponent<Collider2D>()->GetColliderPos();

			float dist = sqrt(
				(TargetPos.x - OwnerPos.x) * (TargetPos.x - OwnerPos.x) +
				(TargetPos.y - OwnerPos.y) * (TargetPos.y - OwnerPos.y));

			float MinArea = (float)Owner->GetChampInfo().RNG * 0.9f;

			if (dist > MinArea)
				return NS_SUCCESS;

			return 	NS_FAILURE;
		}
	};
	class Con_IsLeft : public Condition_Node // 왼쪽방향 컨디션
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();

			if (mtr->IsLeft())
				return NS_SUCCESS;
			else
				return NS_FAILURE;
		}
	};
	class Con_IsRight : public Condition_Node // 오른쪽 방향 컨디션
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();

			if (mtr->IsRight())
				return NS_SUCCESS;
			else
				return NS_FAILURE;
		}
	};
	class Con_OntheLeft : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* Owner = mAIBB->FindData<Champ>(*ChampName);
			Vector3 OwnerPos = Owner->GetComponent<Collider2D>()->GetColliderPos();
			Vector3 TargetPos = Owner->GetEnemys().begin()->second->GetComponent<Collider2D>()->GetColliderPos();

			if (TargetPos.x <= OwnerPos.x)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};
	class Con_OntheRight : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* Owner = mAIBB->FindData<Champ>(*ChampName);
			Vector3 OwnerPos = Owner->GetComponent<Collider2D>()->GetColliderPos();
			Vector3 TargetPos = Owner->GetEnemys().begin()->second->GetComponent<Collider2D>()->GetColliderPos();

			if (TargetPos.x > OwnerPos.x)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};
	class Con_IsOver_LeftArea : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();
			
			int* CenterPos = mAIBB->FindData<int>(L"CenterPos");

			Vector3 pos = mtr->GetPosition();

			if (*CenterPos - 100.f > pos.x)
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
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();
			
			int* CenterPos = mAIBB->FindData<int>(L"CenterPos");
			
			Vector3 pos = mtr->GetPosition();

			if (*CenterPos + 100.f < pos.x)
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
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();

			mtr->SetLeft();
			return NS_SUCCESS;
		}
	};
	class Act_TurnRight : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();

			mtr->SetRight();
			return NS_SUCCESS;
		}
	};
	class Act_MoveLeft : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			GameObject* Owner = mAIBB->FindData<GameObject>(*ChampName);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();
			Vector3 pos = mtr->GetPosition();

			if (Owner->GetLayerType() == eLayerType::Player)
				pos.x -= 150.f * (float)Time::DeltaTime();
			else if (Owner->GetLayerType() == eLayerType::Enemy)
				pos.x -= 80.f * (float)Time::DeltaTime();

			mtr->SetPosition(pos);

			return NS_SUCCESS;
		}
	};
	class Act_MoveRight : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			GameObject* Owner = mAIBB->FindData<GameObject>(*ChampName);

			Transform* mtr = mAIBB->FindData<GameObject>(*ChampName)->GetComponent<Transform>();
			Vector3 pos = mtr->GetPosition();

			if (Owner->GetLayerType() == eLayerType::Player)
				pos.x += 150.f * (float)Time::DeltaTime();
			else if (Owner->GetLayerType() == eLayerType::Enemy)
				pos.x += 80.f * (float)Time::DeltaTime();

			mtr->SetPosition(pos);

			return NS_SUCCESS;
		}
	};
	class Act_PlayAnim_Idle : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* mChamp = mAIBB->FindData<Champ>(*ChampName);

			mChamp->Play_Idle();
			return NS_SUCCESS;
		}
	};
	class Act_PlayAnim_Move : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* mChamp = mAIBB->FindData<Champ>(*ChampName);

			mChamp->Play_Move();
			return NS_SUCCESS;
		}
	};
	class Act_PlayAnim_Attack : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* mChamp = mAIBB->FindData<Champ>(*ChampName);

			mChamp->Play_Attack();

			if (mChamp->GetComponent<Animator>()->IsComplete())
			{
				mChamp->Play_Idle();
				return NS_SUCCESS;
			}

			return NS_RUNNING;
		}
	};
	class Act_PlayAnim_Dead : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* mChamp = mAIBB->FindData<Champ>(*ChampName);
			
			mChamp->Play_Dead();

			if (mChamp->GetComponent<Animator>()->IsComplete())
				return NS_SUCCESS;

			return NS_RUNNING;
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