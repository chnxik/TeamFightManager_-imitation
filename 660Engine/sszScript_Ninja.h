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

	virtual void InitChampInfo();   // 챔프 정보 설정
	virtual void InitChampAnim();   // 챔프 애니메이션 설정
	virtual void InitColObj();      // 챔프 콜라이더오브젝트 설정
	virtual void InitAudio();
	virtual void InitBT();          // 챔프 AI 설정

	virtual void Attack();
	virtual void Skill();


	virtual void Dead();
};

}