#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class Team
	{
	public:
		Team();
		virtual ~Team();

		void InitTeamInfo(const std::wstring& TeamName, std::shared_ptr<Texture> TeamLogo);


		std::shared_ptr<Texture>  GetTeamLogo();

	private:
		std::wstring mTeamName;					// �� �̸�
		std::shared_ptr<Texture> mTeamLogo;		// �� ������
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