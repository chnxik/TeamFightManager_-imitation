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

		virtual void InitChampInfo();   // è�� ���� ����
		virtual void InitChampAnim();   // è�� �ִϸ��̼� ����
		virtual void InitColObj();      // è�� �ݶ��̴�������Ʈ ����
		virtual void InitAudio();
		virtual void InitBT();          // è�� AI ����

		virtual void Dead();
	};
}