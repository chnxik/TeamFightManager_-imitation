#pragma once
#include "sszChamp_Script.h"
#include "CommonObjHeader.h"

namespace ssz
{
	class Script_Knight : public Champ_Script
	{
	public:
		Script_Knight();
		virtual ~Script_Knight();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void InitChampInfo();   // 챔프 정보 설정
		virtual void InitChampAnim();   // 챔프 애니메이션 설정
		virtual void InitColObj();      // 챔프 콜라이더오브젝트 설정
		virtual void InitBT();          // 챔프 AI 설정

		virtual void Dead();

		virtual void Play_Idle();
		virtual void Play_Move();
		virtual void Play_Attack();
		virtual void Play_Dead();
		virtual void Play_Skill1();
		virtual void Play_Skill2();
	};
}