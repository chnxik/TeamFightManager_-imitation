#pragma once
#include "sszChamp_Script.h"
#include "CommonObjHeader.h"

namespace ssz
{
	class Script_Archer : public Champ_Script
	{
	public:
		Script_Archer();
		virtual ~Script_Archer();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void InitChampInfo();   // è�� ���� ����
		virtual void InitChampAnim();   // è�� �ִϸ��̼� ����
		virtual void InitColObj();      // è�� �ݶ��̴�������Ʈ ����
		virtual void InitBT();          // è�� AI ����

		virtual void Dead();

		virtual void Play_Idle();
		virtual void Play_Move();
		virtual void Play_Attack();
		virtual void Play_Dead();
		virtual void Play_Skill1();
		virtual void Play_Skill2();

	};
}