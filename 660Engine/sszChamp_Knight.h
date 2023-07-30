#pragma once
#include "sszChamp.h"

namespace ssz
{
	class Champ_Knight : public Champ
	{
	public:
		Champ_Knight();
		virtual ~Champ_Knight();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		virtual void SetAnimator();

		virtual void Play_Idle();
		virtual void Play_Move();
		virtual void Play_Attack();
		virtual void Play_Dead();
		virtual void Play_Skill1();
		virtual void Play_Skill2();

		virtual void Attack();
		virtual void Dead();

	private:

	};
}