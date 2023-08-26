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
#pragma region Serch Target Ÿ�� �˻�
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
#pragma region Trasnfrom Condition ��ġ �Ǵ�
	// ��ǥ ���� ���� �Ǵ�
	class Con_IsArrive : public Condition_Node // MovePoint ���� ����
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
				return NS_FAILURE; // �����ؼ� ���ο� �̵������� Ȯ���ؾ���.

			return NS_SUCCESS;	// �������� ����
		}
	};
	// �Ÿ� ���� �Ǵ�
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
			float MinArea = (float)Target->GetChampInfo().RNG;	// �� è�Ǿ� �����Ÿ�

			if (dist > MinArea)
				return NS_SUCCESS;

			return 	NS_FAILURE;
		}
	};
#pragma endregion
#pragma region Status Condition ���� �Ǵ�
	// ����Ǵ� : DeadAnimationȮ��
	class Con_IsAlive : public Condition_Node // �������
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->IsChampDead())
				return NS_RUNNING;	// ��� �ִϸ��̼� �����

			return NS_FAILURE;
		}
	};
	// ����� �Ǵ� : ���, ����
#pragma endregion
#pragma region Active Check	��ȣ�ۿ� ���� üũ
	class Con_CheckActive_Attack_CoolTime : public Condition_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Champ::tChampStatus* status = Owner->GetChampStatus();

			// ��Ÿ�� ��밡���� �ð�����.
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

			// ��Ÿ�� ��밡���� �ð�����.
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

			// ���� ���ð��� �ñر��밡�ɽð��� �Ѿ�����
			Champ::tChampStatus* status = Owner->GetChampStatus();

			if (status->bULTIMATE)	// �ñر� ��� �ߴ���.
				return NS_FAILURE;

			// ��Ÿ�� ��밡���� �ð�����.
			
			if (status->UltimateUseTime <= (60.f - TGM::GetGameTime()))
				return NS_SUCCESS;

			return NS_FAILURE;
		}
	};

	// ����, ��ų, �ñر� ��Ÿ� �Ǵ� Contition
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

			// �浹ü�� Ȱ���� �Ǵ�
			if (CollisionManager::IsCollision(TargetCol, OwnerCol))
				return NS_SUCCESS;

			/*	pos�� Ȱ���� �Ÿ� ��� ��
			Champ::tChampStatus* status = Owner->GetChampStatus();

			Vector2 OwnerPos = Owner->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 TargetPos = Target->GetComponent<Transform>()->GetWorldPosition().V3toV2();

			float dist = Vector2::Distance(OwnerPos, TargetPos);
			if ((status->ChampInfo.RNG * 2.f) >= dist)	// ��Ÿ� ���̴�.
				return NS_SUCCESS;
			*/

			return NS_FAILURE;
		}
	};

	// ���� �Ǵ�
	// ���Ÿ�
	// �̿� ü��,�̵��ӵ� �Ǵ�
#pragma endregion

	// =============
	// [Action Node]
	// =============

#pragma region Set Move Point �̵� ����Ʈ ����
	// ī���� ����
	class Act_SetMovePoint_Kiting : public Action_Node
	{
	private:
		float RandomDtoR(float degree)
		{
			float value = (float)(rand() % 30) - 15;	// 30�� ����

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

			Champ* Target = Owner->GetTarget_Enemy(); // Ÿ�� ��ġ

			if (Target == nullptr)
				return NS_FAILURE;

			// �Ϲ����� ī���� : Ÿ�� ��ġ�� �� �ݴ� �������� �̵�
			Vector2 OwnerPos = Owner->GetComponent<Transform>()->GetWorldPosition().V3toV2();
			Vector2 TargetPos = Target->GetComponent<Transform>()->GetWorldPosition().V3toV2();

			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);

			// ������ ��ġ
			// Ÿ����ġ���� ���� �ٹ��� ��Ÿ� �Ÿ���ŭ�� ������ ��ġ

			Vector2 vPos = OwnerPos - TargetPos;									// Target ���� Owner ����
			float fDegree = atan2(vPos.y, vPos.x) * 180.f / (float)_Pi;		// radian ��
			fDegree = RandomDtoR(fDegree);
			float range = (float)Owner->GetChampInfo().RNG;
			vPos.x = TargetPos.x + cos(fDegree) * range;
			vPos.y = TargetPos.y + sin(fDegree) * range;
			
			*MovePoint = vPos;

			RECT stadiumSize = TGM::GetStadiumSize();

			// ����ó�� MovePoint�� ������� ����� ��
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
	
	// ������ ����
	class Act_SetMovePoint_Random : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Champ* Target = Owner->GetTarget_Enemy(); // Ÿ�� ��ġ
			
			Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);
			

			*MovePoint = Vector2((float)rand(), (float)rand());;	// ��������
			(*MovePoint).Normalize();				// ����ȭ�Ͽ� ���� ���
			*MovePoint *= ((float)(rand() % 100) + 10.f);	// 10 ~ 100px ������ ������ �Ÿ�

			RECT stadiumSize = TGM::GetStadiumSize();

			// ����ó�� MovePoint�� ������� ����� ��
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
#pragma region Transform Action �̵����� �ൿ
	// �⺻ �̵�
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
			// 	return NS_SUCCESS;	// ���ο� �̵������� 5�ȼ� �̳��� �̵����� �ʴ´�

			Vector2 dir = (*MovePoint) - OwnerPos.V3toV2();
			dir.Normalize(); // ����ȭ�Ͽ� ���� ���

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
	// ���� �̵�

	// ������ȯ
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
#pragma region Animation �ִϸ��̼� ���
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