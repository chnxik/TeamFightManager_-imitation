#pragma once
#include "sszCommonBT.cpp"

namespace ssz
{
	// ==============
	// [Actione Node]
	// ==============

	class Act_Skill_Archer : public Action_Node
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
				Champ* Target = Owner->GetTarget_Enemy();
				Vector2 TargetPos = Target->GetComponent<Transform>()->GetPosition().V3toV2();

				vDir = OwnerPos.V3toV2() - TargetPos;
				vDir.Normalize();

				fJumpRatio = 0.f;

				Owner->Play_Skill();
			}
			else if (Owner->GetComponent<Animator>()->IsComplete())
			{
				Vector2* MovePoint = FINDBBDATA(Vector2, MOVEPOINT);
				*MovePoint = OwnerPos.V3toV2();	// 스킬 종료 후 MOVEPOINT 초기화

				return NS_SUCCESS;
			}

			fJumpRatio += (float)Time::DeltaTime();

			if (fJumpRatio < 0.4f)	// 점프 이동구간
			{
				OwnerPos.x += (vDir.x * 200.f * (float)Time::DeltaTime());
				OwnerPos.y += (vDir.y * 200.f * (float)Time::DeltaTime());

				RECT stadiumSize = TGM::GetStadiumSize();

				// 예외처리 MovePoint가 경기장을 벗어났을 때
				if (OwnerPos.x <= stadiumSize.left)
					OwnerPos.x = stadiumSize.left + 2.f;
				else if (OwnerPos.x >= stadiumSize.right)
					OwnerPos.x = stadiumSize.right - 2.f;

				if (OwnerPos.y >= stadiumSize.top)
					OwnerPos.y = stadiumSize.top - 2.f;
				else if (OwnerPos.y <= stadiumSize.bottom)
					OwnerPos.y = stadiumSize.bottom + 2.f;

				tr->SetPosition(OwnerPos);
			}

			return NS_RUNNING;
		}

	private:
		Vector2 vDir;
		float fJumpRatio;
	};
}