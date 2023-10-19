#pragma once
#include "sszCommonBT.cpp"
#include "sszScript_Ninja.h"

#include "sszTGM.h"
#include "sszEffect.h"

namespace ssz
{
	// ==============
	// [Actione Node]
	// ==============

	class Act_Attack_Ninja : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::ATTACK))
			{
				fAttackRatio = 0.f;
				bDamage = false;
				Owner->Play_Attack();
			}

			else if (Owner->GetComponent<Animator>()->IsComplete())
			{
				Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);
				*MovePoint = Owner->GetComponent<Transform>()->GetPosition().V3toV2();	// 스킬 종료 후 MOVEPOINT 초기화

				return NS_SUCCESS;
			}

			fAttackRatio += (float)Time::DeltaTime();

			if (0.35f < fAttackRatio && !bDamage)	// 타격지점
			{
				bDamage = true;
			}

			return NS_RUNNING;
		}

	private:
		bool bDamage = false;
		float fAttackRatio = 0.f;
	};

	class Act_Skill_Ninja : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			Transform* tr = Owner->GetComponent<Transform>();
			Vector3 OwnerPos = tr->GetPosition();

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::SKILL))
			{
				fJumpRatio = 0.f;
				bMoving = false;

				Owner->Play_Skill();
				Vector3 Scale(170.f, 170.f, 0.f);
				
				TGM::GetEffectObj()->Play(OwnerPos, Scale, L"ninja_skill_1");
			}
			else if (Owner->GetComponent<Animator>()->IsComplete())
			{
				Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);
				*MovePoint = OwnerPos.V3toV2();	// 스킬 종료 후 MOVEPOINT 초기화

				return NS_SUCCESS;
			}

			fJumpRatio += (float)Time::DeltaTime();


			if (0.8f < fJumpRatio && !bMoving)	// 점프 이동구간
			{
				Champ* Target = Owner->GetTarget_Enemy();
				
				Vector3 TargetPos;
				if (Target)
					TargetPos = Target->GetComponent<Transform>()->GetPosition();
				else
					TargetPos = OwnerPos;
					
				TargetPos.x += 50.f;
				
				RECT stadiumSize = TGM::GetStadiumSize();

				// 예외처리 MovePoint가 경기장을 벗어났을 때
				if (TargetPos.x <= stadiumSize.left)
					TargetPos.x = stadiumSize.left + 2.f;
				else if (TargetPos.x >= stadiumSize.right)
					TargetPos.x = stadiumSize.right - 2.f;

				if (TargetPos.y >= stadiumSize.top)
					TargetPos.y = stadiumSize.top - 2.f;
				else if (TargetPos.y <= stadiumSize.bottom)
					TargetPos.y = stadiumSize.bottom + 2.f;

				tr->SetPosition(TargetPos);

				bMoving = true;

				Vector3 Scale(170.f, 170.f, 0.f);
				
				BattleManager::ATTACK(Owner, Owner->GetTarget_Enemy(), Owner->GetChampInfo().ATK * 1.2f);
				TGM::GetEffectObj()->Play(TargetPos, Scale, L"ninja_skill_2");
			}

			return NS_RUNNING;
		}

	private:
		bool bMoving = false;
		float fJumpRatio = 0.f;;
	};
}