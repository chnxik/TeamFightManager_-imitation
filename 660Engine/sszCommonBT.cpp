#pragma once
#include "CommonObjHeader.h"
#include "sszBattleManager.h"
#include "sszLog.h"

namespace ssz
{
#pragma region Test BT
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

	class Con_IsDead : public Condition_Node // 사망여부
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* Owner = mAIBB->FindData<Champ>(*ChampName);

			Animator* Anim = Owner->GetComponent<Animator>();
			if (Anim->GetCurAnimationKey() == Owner->GetAnimKey(Champ::eActiveType::DEAD))
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

			if (CollisionManager::IsCollision(OwnerCol, CsrCol))
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

			Collider2D* OwnerCol = Owner->GetColObjsCol(eColObjType::RANGE);
			Collider2D* TargetCol = nullptr;

			Champ* Target = Owner->GetEnemys()[0];
			TargetCol = Target->GetComponent<Collider2D>();

			if (CollisionManager::IsCollision(TargetCol, OwnerCol))
			{
				Owner->SetTarget_Enemy(Target);
				return NS_SUCCESS;
			}


			return NS_FAILURE;
		}
	};

	class Con_MustBack : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = mAIBB->FindData<wstring>(CHAMPKEY);

			Champ* Owner = mAIBB->FindData<Champ>(*ChampName);

			Vector3 TargetPos = Owner->GetEnemys()[0]->GetComponent<Collider2D>()->GetColliderPos();
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
			Vector3 TargetPos = Owner->GetEnemys()[0]->GetComponent<Collider2D>()->GetColliderPos();

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
			Vector3 TargetPos = Owner->GetEnemys()[0]->GetComponent<Collider2D>()->GetColliderPos();

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
	class Act_MoveLeft : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring,CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ,*ChampName);

			Transform* tr = Owner->GetComponent<Transform>();
			
			Vector3 pos = tr->GetPosition();

			if (Owner->GetLayerType() == eLayerType::Player)
				pos.x -= 150.f * (float)Time::DeltaTime();
			else if (Owner->GetLayerType() == eLayerType::Enemy)
				pos.x -= 80.f * (float)Time::DeltaTime();

			tr->SetPosition(pos);

			return NS_SUCCESS;
		}
	};
	class Act_MoveRight : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

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
#pragma endregion

	// ================
	// [Condition Node]
	// ================
#pragma region Target Check
	class Con_SerchTarget_Enemy_HPMIN : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);
			Champ* Target = Owner->GetTarget_Enemy();

			for (Champ* pChamp : Owner->GetEnemys())
			{
				if (pChamp != nullptr &&
					pChamp->IsActive())
				{
					if (Target == nullptr)
					{
						Target = pChamp;
					}
					else if (pChamp->GetChampStatus()->HP <
						Target->GetChampStatus()->HP)
					{
						Target = pChamp;
					}
				}
			}

			if (Target == nullptr)
				return NS_FAILURE;

			return NS_SUCCESS;
		}
	};
	class Con_SerchTarget_Enemy_ChampType : public Condition_Node
	{
	public:
		Con_SerchTarget_Enemy_ChampType(eChampType type) : mChampType(type) {}

		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);
			Champ* Target = Owner->GetTarget_Enemy();

			for (Champ* pChamp : Owner->GetEnemys())
			{
				if (pChamp != nullptr &&
					pChamp->IsActive())
				{
					if (Target == nullptr)
					{
						Target = pChamp;
					}
					else if (pChamp->GetChampInfo().ChampType == mChampType)
					{
						Target = pChamp;
					}
				}
			}

			if (Target == nullptr)
				return NS_FAILURE;

			return NS_SUCCESS;
		}

	private:
		eChampType mChampType;
	};
	class Con_SerchTarget_Enemy_Near : public Condition_Node
	{
	private:
		Champ* NearChamp(Champ* Owner, Champ* A, Champ* B)
		{
			Vector2 OwnerPos = Owner->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 APos = A->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 BPos = B->GetComponent<Transform>()->GetWorldPosition().V3toV2();

			float Adist = Vector2::Distance(OwnerPos, APos);
			float Bdist = Vector2::Distance(OwnerPos, BPos);

			if (Adist > Bdist)
				return B;

			else
				return A;
		}

	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);
			Champ* Target = Owner->GetTarget_Enemy();

			for (Champ* pChamp : Owner->GetEnemys())
			{
				if (pChamp != nullptr &&
					pChamp->IsActive())
				{
					if (Target == nullptr)
					{
						Target = pChamp;
						continue;
					}

					Target = NearChamp(Owner, Target, pChamp);
				}
			}

			if (Target == nullptr)
				return NS_FAILURE;

			return NS_SUCCESS;
		}
	};
	class Con_SerchTarget_Friendly_HPMIN : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);
			Champ* Target = Owner->GetTarget_Friendly();

			for (Champ* pChamp : Owner->GetFriendly())
			{
				if (pChamp != nullptr &&
					pChamp->IsActive())
				{
					if (Target == nullptr)
					{
						Target = pChamp;
					}
					else if (pChamp->GetChampStatus()->HP <
						Target->GetChampStatus()->HP)
					{
						Target = pChamp;
					}
				}
			}

			if (Target == nullptr)
				return NS_FAILURE;

			return NS_SUCCESS;
		}
	};
#pragma endregion

#pragma region Active Check
	class Con_CheckActive_Skill : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Champ::tChampStatus* status = Owner->GetChampStatus();

			// 쿨타임 사용가능한 시간인지.
			if (status->CoolTime_Skill <= status->accTime_Skill)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};

	class Con_CheckActive_Ultimate : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			// 현재 경기시간이 궁극기사용가능시간을 넘었는지
			return NS_SUCCESS;
		}
	};

	// 공격, 스킬, 궁극기 사거리 판단 Contition
#pragma endregion

	// =============
	// [Action Node]
	// =============

#pragma region Set Move Point
	// 카이팅 무빙
	class Act_SetMovePoint_Kiting: public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Champ* Target = Owner->GetTarget_Enemy(); // 타겟 위치

			// 일반적인 카이팅 : 타겟 위치의 정 반대 방향으로 이동
			Vector2 OwnerPos = Owner->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 TargetPos = Target->GetComponent<Transform>()->GetWorldPosition().V3toV2();

			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);

			
			


			return NS_SUCCESS;
		}
	};
	// 타겟 방향 무빙
	class Act_SetMovePoint_Target : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			return NS_SUCCESS;
		}
	};
	// 무작위 무빙
	class Act_SetMovePoint_Random : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			return NS_SUCCESS;
		}
	};
#pragma endregion

#pragma region Transform Action
	// 강제 이동
	// 어택 이동
	class Act_TurnLeft : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Transform* tr = Owner->GetComponent<Transform>();
			tr->SetLeft();
			return NS_SUCCESS;
		}
	};
	class Act_TurnRight : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Transform* tr = Owner->GetComponent<Transform>();
			tr->SetRight();
			return NS_SUCCESS;
		}
	};
#pragma endregion

#pragma region Animation
	// Idle
	class Act_PlayAnim_Idle : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::IDLE))
				Owner->Play_Idle();

			return NS_SUCCESS;
		}
	};
	// Move
	class Act_PlayAnim_Move : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::MOVE))
				Owner->Play_Move();

			return NS_SUCCESS;
		}
	};
	// Attack
	class Act_PlayAnim_Attack : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::ATTACK))
				Owner->Play_Attack();

			else if (Owner->GetComponent<Animator>()->IsComplete())
				return NS_SUCCESS;

			return NS_RUNNING;
		}
	};
	// Skill
	class Act_PlayAnim_Skill : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::SKILL))
				Owner->Play_Skill();

			else if (Owner->GetComponent<Animator>()->IsComplete())
				return NS_SUCCESS;

			return NS_RUNNING;
		}
	};
	// Ultimate
	class Act_PlayAnim_Ultimate : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::ULTIMATE))
				Owner->Play_Ultimate();

			else if (Owner->GetComponent<Animator>()->IsComplete())
				return NS_SUCCESS;

			return NS_RUNNING;
		}
	};
	// Dead
	class Act_PlayAnim_Dead : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::DEAD))
				Owner->Play_Dead();

			if (Owner->GetComponent<Animator>()->IsComplete())
				return NS_SUCCESS;

			return NS_RUNNING;
		}
	};
#pragma endregion
}