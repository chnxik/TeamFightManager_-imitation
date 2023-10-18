#pragma once
#include "sszTexture.h"

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

		void RegistPilot(Pilot* pilot);

		const UINT* GetTKScoreAddress() { return &mCurGameTKScore; }
		void AddKillScore() { mCurGameTKScore++; }
		void ResetGameInfo() { mCurGameTKScore = 0; }

		std::vector<Pilot*> GetPilotList() { return mPilotList; }

	private:
		std::wstring mTeamName;					// �� �̸�
		std::shared_ptr<Texture> mTeamIcon;		// �� ������
		std::wstring mTeamIconTexKey;
		// �� ����
		UINT mCurGameTKScore;

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