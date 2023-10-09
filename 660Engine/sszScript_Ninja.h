#pragma once
#include "sszChamp_Script.h"

namespace ssz
{

class Script_Ninja :
    public Champ_Script
{
	Script_Ninja();
	virtual ~Script_Ninja();

	virtual void Initialize() override;
	virtual void Update() override;

	virtual void InitChampInfo();   // è�� ���� ����
	virtual void InitChampAnim();   // è�� �ִϸ��̼� ����
	virtual void InitColObj();      // è�� �ݶ��̴�������Ʈ ����
	virtual void InitAudio();
	virtual void InitBT();          // è�� AI ����

	virtual void Attack();
	virtual void Skill();


	virtual void Dead();
};

}