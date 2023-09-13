#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class Team
	{
	public:
		Team();
		virtual ~Team();

		void SetTeamTex(const std::wstring& LogoTexKey);
		void SetTeamName(const std::wstring& name);

	private:
		std::wstring mTeamLogoTexKey;	// �� �ΰ�
		std::wstring mTeamName;					// �� �̸�
		// �� ����
		
		// ���� è�Ǿ� ���� (è�Ǿ� ����Ʈ���� �޾ƿ´�)
		// ����Ƚ��
		// �¸�
		// �й�
		// �·�
		// ����
		
		// �������� ���� Pilot Map

	};
}