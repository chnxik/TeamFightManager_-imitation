#pragma once
#include "sszCommonBT.cpp"
#include "sszScript_Priest.h"

namespace ssz
{
	// ==============
	// [Actione Node]
	// ==============

	class Act_Heal_Priest : public Action_Node
	{
	public:
		virtual eNodeStatus Run() override
		{
			wstring* ChampName = FINDBBDATA(wstring, CHAMPKEY);
			Champ* Owner = FINDBBDATA(Champ, *ChampName);

			if (Owner->GetComponent<Animator>()->GetCurAnimationKey() !=
				Owner->GetAnimKey(Champ::eActiveType::ATTACK))
			{
				Owner->Play_Attack();
			}

			else if (Owner->GetComponent<Animator>()->IsComplete())
			{
				Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);
				*MovePoint = Owner->GetComponent<Transform>()->GetPosition().V3toV2();	// 스킬 종료 후 MOVEPOINT 초기화

				return NS_SUCCESS;
			}
			return NS_RUNNING;
		}

	private:
	};
}