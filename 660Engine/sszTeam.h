#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class Team
	{
	public:
		Team();
		virtual ~Team();

		void InitTeamInfo(std::wstring TeamName, std::shared_ptr<Texture> TeamIcon);


		std::wstring GetTeamName() { return mTeamName; }
		std::shared_ptr<Texture>  GetTeamIcon() { return mTeamIcon;	}

	private:
		std::wstring mTeamName;					// �� �̸�
		std::shared_ptr<Texture> mTeamIcon;		// �� ������
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