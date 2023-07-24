#pragma once
#include "sszTestScript.h"
#include "CommonObjHeader.h"
#include "sszSceneManager.h"

namespace ssz
{
	class CheckStop : public BT
	{
	private:
		Animator* Anim;

	public:
		CheckStop(Animator* pAnim) : Anim(pAnim) {}


		virtual bool Run() override
		{
			//
			int* Testint = Blackboard::FindData<int>(L"Testint");
			int Test2 = *Testint;
			*Testint = 700;


			//
			Scene* CurScene = SceneManager::GetActiveScene();

			GameObject* Cursor = CurScene->GetLayer(eLayerType::Cursor).GetGameObjects().front();

			Vector3 CsrPos = Cursor->GetComponent<Transform>()->GetWorldPosition();
			Transform* Ownertr = Anim->GetOwner()->GetComponent<Transform>();
			Vector3 OwnerPos = Ownertr->GetWorldPosition();

			float dist = sqrt(
				(CsrPos.x - OwnerPos.x) * (CsrPos.x - OwnerPos.x) +
				(CsrPos.y - OwnerPos.y) * (CsrPos.y - OwnerPos.y));

			if (Input::GetKey(eKeyCode::SPACE))
			{
				Anim->PlayAnimation(L"archer_idle", true);

				return true;
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

				return true;
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

				return true;
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

				return true;
			}

			Anim->PlayAnimation(L"archer_move", true);



			return false;
		}
	};

	class CheckLeft : public BT // sequence
	{
	private:
		Transform* mtr;

	public:
		CheckLeft(Transform* tr) : mtr(tr) {}


		virtual bool Run() override
		{
			if (mtr->IsLeft())
				return true;
			else
				return false;
		}
	};

	class CheckRight : public BT // sequence
	{
	private:
		Transform* mtr;

	public:
		CheckRight(Transform* tr) : mtr(tr) {}


		virtual bool Run() override
		{
			if (mtr->IsRight())
				return true;
			else
				return false;
		}
	};

	class CheckLeftDist : public BT
	{
	private:
		Transform* mtr;

	public:
		CheckLeftDist(Transform* tr) : mtr(tr) {}

		virtual bool Run() override
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

			return true;
		}
	};

	class CheckRightDist : public BT
	{
	private:
		Transform* mtr;

	public:
		CheckRightDist(Transform* tr) : mtr(tr) {}

		virtual bool Run() override
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

			return true;
		}
	};
}