#pragma once
#include "sszTestScript.h"
#include "CommonObjHeader.h"

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
			if (Input::GetKey(eKeyCode::SPACE))
			{
				if (!(Anim->GetCurAnimation() == L"archer_idle"))
					Anim->PlayAnimation(L"archer_idle", true);

				return true;
			}

			if (!(Anim->GetCurAnimation() == L"archer_move"))
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