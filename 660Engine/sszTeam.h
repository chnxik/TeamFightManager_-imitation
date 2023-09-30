#pragma once


namespace ssz
{
	class Pilot;

	class Team
	{
	public:
		Team();
		virtual ~Team();

		void InitTeamInfo(std::wstring TeamName, std::shared_ptr<Texture> TeamIcon);
		void SetTeamName(std::wstring TeamName);
		void SetIconTex(std::wstring TexKey);

		std::wstring GetTeamName() { return mTeamName; }
		std::shared_ptr<Texture>  GetTeamIcon() { return mTeamIcon;	}
		std::wstring GetTeamIconTexKey() { return mTeamIconTexKey; }

		void AddPilot(Pilot* pilot);

	private:
		std::wstring mTeamName;					// �� �̸�
		std::shared_ptr<Texture> mTeamIcon;		// �� ������
		std::wstring mTeamIconTexKey;
		// �� ����
		
		// ���� è�Ǿ� ���� (è�Ǿ� ����Ʈ���� �޾ƿ´�)
		// ����Ƚ��
		// �¸�
		// �й�
		// �·�
		// ����
		
		// �������� ���� Pilot Map
		std::vector<Pilot*> mPilotList;

	};
}