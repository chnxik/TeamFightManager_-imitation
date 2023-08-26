#pragma once
#include "CommonObjHeader.h"
#include "sszBattleManager.h"
#include "sszLog.h"
#include "sszTGM.h"

namespace ssz
{


	// ================
	// [Condition Node]
	// ================
#pragma region Serch Target 타겟 검색
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
					if (pChamp->IsChampDead())
						continue;

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

			Owner->SetTarget_Enemy(Target);
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
					if (pChamp->IsChampDead())
						continue;

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

			Owner->SetTarget_Enemy(Target);
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
					if (pChamp->IsChampDead())
						continue;

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

			Owner->SetTarget_Enemy(Target);
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
			
			Owner->SetTarget_Friendly(Target);
			return NS_SUCCESS;
		}
	};
#pragma endregion
#pragma region Trasnfrom Condition 위치 판단
	// 목표 지점 도착 판단
	class Con_IsArrive : public Condition_Node // MovePoint 도착 여부
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Transform* tr = Owner->GetComponent<Transform>();
			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);

			if (Vector2::Distance(tr->GetWorldPosition().V3toV2(), (*MovePoint))
				< 1.f)
				return NS_FAILURE; // 도착해서 새로운 이동지점을 확인해야함.

			return NS_SUCCESS;	// 도착하지 않음
		}
	};
	// 거리 후퇴 판단
	class Con_Retreat_Dist : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);
			Champ* Target = Owner->GetTarget_Enemy();

			Vector2 OwnerPos = Owner->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 TargetPos = Target->GetComponent<Collider2D>()->GetColliderPos().V3toV2();

			float dist = Vector2::Distance(OwnerPos, TargetPos);
			float MinArea = (float)Target->GetChampInfo().RNG;	// 적 챔피언 사정거리

			if (dist > MinArea)
				return NS_SUCCESS;

			return 	NS_FAILURE;
		}
	};
#pragma endregion
#pragma region Status Condition 상태 판단
	// 사망판단 : DeadAnimation확인
	class Con_IsAlive : public Condition_Node // 사망여부
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->IsChampDead())
				return NS_RUNNING;	// 사망 애니메이션 재생중

			return NS_FAILURE;
		}
	};
	// 디버프 판단 : 에어본, 스턴
#pragma endregion
#pragma region Active Check	상호작용 가능 체크
	class Con_CheckActive_Attack_CoolTime : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Champ::tChampStatus* status = Owner->GetChampStatus();

			// 쿨타임 사용가능한 시간인지.
			if (status->accTime_Attack >= 1.f)
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};
	class Con_CheckActive_Skill_CoolTime : public Condition_Node
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

			// 

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
			Champ::tChampStatus* status = Owner->GetChampStatus();

			if (status->bULTIMATE)	// 궁극기 사용 했는지.
				return NS_FAILURE;

			// 쿨타임 사용가능한 시간인지.
			
			if (status->UltimateUseTime <= (60.f - TGM::GetGameTime()))
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};

	// 공격, 스킬, 궁극기 사거리 판단 Contition
	class Con_CheckRagne_Attack : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);
			Champ* Target = Owner->GetTarget_Enemy();

			Collider2D* OwnerCol = Owner->GetColObjsCol(eColObjType::RANGE);
			Collider2D* TargetCol = Target->GetComponent<Collider2D>();

			// 충돌체를 활용한 판단
			if (CollisionManager::IsCollision(TargetCol, OwnerCol))
				return NS_SUCCESS;

			/*	pos를 활용한 거리 계산 시
			Champ::tChampStatus* status = Owner->GetChampStatus();

			Vector2 OwnerPos = Owner->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 TargetPos = Target->GetComponent<Transform>()->GetWorldPosition().V3toV2();

			float dist = Vector2::Distance(OwnerPos, TargetPos);
			if ((status->ChampInfo.RNG * 2.f) >= dist)	// 사거리 안이다.
				return NS_SUCCESS;
			*/

			return NS_FAILURE;
		}
	};

	// 후퇴 판단
	// 원거리
	// 이외 체력,이동속도 판단
#pragma endregion

	// =============
	// [Action Node]
	// =============

#pragma region Set Move Point 이동 포인트 지정
	// 카이팅 무빙
	class Act_SetMovePoint_Kiting : public Action_Node
	{
	private:
		float RandomDtoR(float degree)
		{
			float value = (float)(rand() % 30) - 15;	// 30도 범위

			value = degree + value;

			if (value <= -180.f)
				value = 180.f + (180.f + value);
			else if (value >= 180)
				value = -180.f + (-180.f + value);

			value *= (float)_Pi / 180.f;
			
			return value;
		}

	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Champ* Target = Owner->GetTarget_Enemy(); // 타겟 위치

			if (Target == nullptr)
				return NS_FAILURE;

			// 일반적인 카이팅 : 타겟 위치의 정 반대 방향으로 이동
			Vector2 OwnerPos = Owner->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 TargetPos = Target->GetComponent<Transform>()->GetWorldPosition().V3toV2();

			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);

			// 얻고싶은 위치
			// 타겟위치에서 오너 근방의 사거리 거리만큼의 랜덤한 위치

			Vector2 vPos = OwnerPos - TargetPos;									// Target 에서 Owner 방향
			float fDegree = atan2(vPos.y, vPos.x) * 180.f / (float)_Pi;		// radian 값
			fDegree = RandomDtoR(fDegree);
			float range = (float)Owner->GetChampInfo().RNG;
			vPos.x = TargetPos.x + cos(fDegree) * range;
			vPos.y = TargetPos.y + sin(fDegree) * range;
			
			*MovePoint = vPos;

			RECT stadiumSize = TGM::GetStadiumSize();

			// 예외처리 MovePoint가 경기장을 벗어났을 때
			if ((*MovePoint).x <= stadiumSize.left)
				(*MovePoint).x = stadiumSize.left + 20.f;
			else if ((*MovePoint).x >= stadiumSize.right)
				(*MovePoint).x = stadiumSize.right - 20.f;

			if ((*MovePoint).y >= stadiumSize.top)
				(*MovePoint).y = stadiumSize.top - 20.f;
			else if ((*MovePoint).y <= stadiumSize.bottom)
				(*MovePoint).y = stadiumSize.bottom + 20.f;

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

			Champ* Target = Owner->GetTarget_Enemy(); // 타겟 위치
			
			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);
			

			*MovePoint = Vector2((float)rand(), (float)rand());;	// 랜덤방향
			(*MovePoint).Normalize();				// 정규화하여 방향 얻기
			*MovePoint *= ((float)(rand() % 100) + 10.f);	// 10 ~ 100px 사이의 랜덤한 거리

			RECT stadiumSize = TGM::GetStadiumSize();

			// 예외처리 MovePoint가 경기장을 벗어났을 때
			if ((*MovePoint).x <= stadiumSize.left)
				(*MovePoint).x = stadiumSize.left + 20.f;
			else if ((*MovePoint).x >= stadiumSize.right)
				(*MovePoint).x = stadiumSize.right - 20.f;

			if ((*MovePoint).y >= stadiumSize.top)
				(*MovePoint).y = stadiumSize.top - 20.f;
			else if ((*MovePoint).y <= stadiumSize.bottom)
				(*MovePoint).y = stadiumSize.bottom + 20.f;

			return NS_SUCCESS;
		}
	};
#pragma endregion
#pragma region Transform Action 이동관련 행동
	// 기본 이동
	class Act_Move_Default : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Transform* tr = Owner->GetComponent<Transform>();
			Champ::tChampInfo info = Owner->GetChampInfo();
			Vector3 OwnerPos = tr->GetPosition();

			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);

			// if (Vector2::Distance(OwnerPos.V3toV2(), *MovePoint) < 5.f)
			// 	return NS_SUCCESS;	// 새로운 이동지점이 5픽셀 이내면 이동하지 않는다

			Vector2 dir = (*MovePoint) - OwnerPos.V3toV2();
			dir.Normalize(); // 정규화하여 방향 얻기

			if (dir.x < 0)
				tr->SetLeft();
			else
				tr->SetRight();
			
			OwnerPos.x += (dir.x * info.SPD * 20.f * (float)Time::DeltaTime());
			OwnerPos.y += (dir.y * info.SPD * 20.f * (float)Time::DeltaTime());

			tr->SetPosition(OwnerPos);

			return NS_SUCCESS;
		}
	};
	// 강제 이동

	// 방향전환
	class Act_SetDir_Target : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Transform* Ownertr = Owner->GetComponent<Transform>();
			Vector3 OwnerPos = Ownertr->GetWorldPosition();
			Vector3 TargetPos = Owner->GetTarget_Enemy()->GetComponent<Transform>()->GetWorldPosition();

			if (OwnerPos.x < TargetPos.x)
				Ownertr->SetRight();
			else
				Ownertr->SetLeft();

			return NS_SUCCESS;
		}
	};
	class Act_SetDir_MovePoint : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Transform* Ownertr = Owner->GetComponent<Transform>();
			Vector3 OwnerPos = Ownertr->GetWorldPosition();
			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);

			if (OwnerPos.x < (*MovePoint).x)
				Ownertr->SetRight();
			else
				Ownertr->SetLeft();

			return NS_SUCCESS;
		}
	};
#pragma endregion
#pragma region Animation 애니메이션 재생
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