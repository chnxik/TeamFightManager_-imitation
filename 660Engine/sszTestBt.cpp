#pragma once
#include "sszTestScript.h"
#include "CommonObjHeader.h"
#include "sszSceneManager.h"

namespace ssz
{
	class CheckStop : public BT
	{
	public:
		CheckStop(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}

		virtual eNodeStatus Run() override
		{
			Scene* CurScene = SceneManager::GetActiveScene();

			GameObject* Cursor = CurScene->GetLayer(eLayerType::Cursor).GetGameObjects().front();

			Vector3 CsrPos = Cursor->GetComponent<Transform>()->GetWorldPosition();

			Transform* Ownertr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();
			Animator* Anim = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Animator>();

			Vector3 OwnerPos = Ownertr->GetWorldPosition();

			float dist = sqrt(
				(CsrPos.x - OwnerPos.x) * (CsrPos.x - OwnerPos.x) +
				(CsrPos.y - OwnerPos.y) * (CsrPos.y - OwnerPos.y));

			if (Input::GetKey(eKeyCode::SPACE))
			{
				Anim->PlayAnimation(L"archer_idle", true);

				return mNodeStatus;
			}
			
			if (300.f < dist && dist < 500.f)
			{
				if (0 <= (CsrPos.x - OwnerPos.x))
				{
					if (Ownertr->IsLeft())
						Ownertr->SetRight();
				}
				else
				{
					if (Ownertr->IsRight())
						Ownertr->SetLeft();
				}

				Anim->PlayAnimation(L"archer_skill", true);

				return SetStatus(NS_SUCCESS);
			}

			if (50.f < dist && dist < 300.f)
			{
				if (0 <= (CsrPos.x - OwnerPos.x))
				{
					if (Ownertr->IsLeft())
						Ownertr->SetRight();
				}
				else
				{
					if (Ownertr->IsRight())
						Ownertr->SetLeft();
				}

				Anim->PlayAnimation(L"archer_attack", true);

				return SetStatus(NS_SUCCESS);
			}

			if (dist < 50.f)
			{
				if (0 <= (CsrPos.x - OwnerPos.x))
				{
					if (Ownertr->IsLeft())
						Ownertr->SetRight();
				}
				else
				{
					if (Ownertr->IsRight())
						Ownertr->SetLeft();
				}

				Anim->PlayAnimation(L"archer_dead", false);

				return SetStatus(NS_SUCCESS);
			}

			Anim->PlayAnimation(L"archer_move", true);

			return 	SetStatus(NS_FAILURE);
		}
	};

	class CheckLeft : public BT // sequence
	{
	public:
		CheckLeft(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}

		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			if (mtr->IsLeft())
				return SetStatus(NS_SUCCESS);
			else
				return SetStatus(NS_FAILURE);
		}
	};

	class CheckRight : public BT // sequence
	{
	public:
		CheckRight(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}
		
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			if (mtr->IsRight())
				return SetStatus(NS_SUCCESS);
			else
				return SetStatus(NS_FAILURE);
		}
	};

	class CheckLeftDist : public BT
	{
	public:
		CheckLeftDist(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}

		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();

		virtual eNodeStatus Run() override
		{
			Vector3 pos = mtr->GetPosition();

			if (-100.f > pos.x)
			{
				mtr->SetRight();
				mtr->SetPosition(pos);

			}
			else
			{
				pos.x -= 100.f * (float)Time::DeltaTime();
				mtr->SetPosition(pos);
			}

			return SetStatus(NS_SUCCESS);
		}
	};

	class CheckRightDist : public BT
	{
	public:
		CheckRightDist(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}
		Transform* mtr = mAIBB->FindData<GameObject>(L"Champ_archer")->GetComponent<Transform>();


		virtual eNodeStatus Run() override
		{
			Vector3 pos = mtr->GetPosition();

			if (100.f < pos.x)
			{
				mtr->SetLeft();
				mtr->SetPosition(pos);
			}
			else
			{
				pos.x += 100.f * (float)Time::DeltaTime();
				mtr->SetPosition(pos);
			}

			return SetStatus(NS_SUCCESS);
		}
	};
}