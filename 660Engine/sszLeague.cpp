#include "sszLeague.h"

#include "sszTGM.h"

#include "sszChamp.h"
#include "sszPilot.h"
#include "sszTeam.h"

namespace ssz
{
	League::League()
		: mCurRound(eRound::Round1)
		, mLeagueSchedule{}
		, mEntry{}
	{
	}
	
	League::~League()
	{
	}

	void League::RoundExit()
	{
		std::queue<Pilot*> ClearQueue;
		
		std::vector<Pilot*> PlayerPilots = GetPlayerTeam()->GetPilotList();
		std::vector<Pilot*> EnemyPilots = GetEnemyTeam()->GetPilotList();

		GetPlayerTeam()->ResetGameInfo();
		GetEnemyTeam()->ResetGameInfo();

		for (int i = 0; i < 2; ++i)
		{
			PlayerPilots[i]->ResetSetting();
			EnemyPilots[i]->ResetSetting();
		}
	}

	void League::NextRound()
	{
		switch (mCurRound)
		{
		case ssz::League::eRound::Round1:
			mCurRound = eRound::Round2;
			break;
		case ssz::League::eRound::Round2:
			mCurRound = eRound::Round3;
			break;
		case ssz::League::eRound::Round3:
			mCurRound = eRound::Round1;
			break;
		}
	}
	
	void League::CreateNewEntry()
	{
		// ���� Entry�� ����

		while (!mEntry.empty())
			mEntry.pop();

		std::map<std::wstring, Team*> tmp = TGM::GetTeamList();
		
		std::map<std::wstring, Team*>::iterator tmpiter = tmp.begin();
		
		std::vector<Team*> TeamList;
		
		// TeamList ���Ϳ� ������ �־��ش�

		while (tmpiter != tmp.end())
		{
			TeamList.emplace_back(tmpiter->second);
			tmpiter++;
		}

		// �����ϰ� ���� �����ش�.

		std::random_device rd;
		std::mt19937 gen(rd());
		std::shuffle(TeamList.begin(), TeamList.end(), gen);

		// �÷��̾����� ���� �տ��ִ� 3���� Entry�� �ִ´�.
		
		for (int i = 0; i < 3; ++i)
			mEntry.push(TeamList[i]);

		// ==================================================================
		
		// Round�� �����Ѵ�
		
		for (int i = 0; i < (UINT)eRound::END; ++i)					// ��ü ����
		{
			tGame GameA , GameB;
			GameA.BlueTeam = TGM::GetPlayerTeam();
			
			GameA.RedTeam = mEntry.front();
			mEntry.pop();
			
			GameB.BlueTeam = mEntry.front();
			mEntry.pop();
			
			GameB.RedTeam = mEntry.front();

			mEntry.push(GameA.RedTeam);
			mEntry.push(GameB.BlueTeam);

			mLeagueSchedule[i][(UINT)eGroup::A] = GameA;
			mLeagueSchedule[i][(UINT)eGroup::B] = GameB;
		}

	}
}