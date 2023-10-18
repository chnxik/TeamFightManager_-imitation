#pragma once
#include "sszCommonBT.cpp"
#include "sszScript_Monk.h"

namespace ssz
{
	// ==============
	// [Actione Node]
	// ==============
	class Act_Attack_Monk : public Action_Node
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
				*MovePoint = Owner->GetComponent<Transform>()->GetPosition().V3toV2();	// ��ų ���� �� MOVEPOINT �ʱ�ȭ

				return NS_SUCCESS;
			}

			fAttackRatio += (float)Time::DeltaTime();

			if (0.35f < fAttackRatio && !bDamage)	// Ÿ������
			{
				Owner->GetChampScript()->Attack();// ����
				bDamage = true;
			}

			return NS_RUNNING;
		}

	private:
		bool bDamage = false;
		float fAttackRatio = 0.f;
	};
}