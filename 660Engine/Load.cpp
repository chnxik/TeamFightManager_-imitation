#include "Load.h"

// Scenes
#include "sszTitleScene.h"
#include "sszMainLobbyScene.h"
#include "sszStadiumScene.h"
#include "sszBanPickScene.h"
#include "sszIGStadiumScene.h"
#include "sszTestScene.h"

#include "sszTGM.h"
#include "sszBattleManager.h"

namespace ssz
{
	void InitializeGame()
	{
		TGM::Initialize();
		BattleManager::Initialize();

		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<MainLobbyScene>(L"MainLobbyScene");
		SceneManager::CreateScene<StadiumScene>(L"StadiumScene");
		SceneManager::CreateScene<BanPickScene>(L"BanPickScene");
		SceneManager::CreateScene<IGStadiumScene>(L"IGStadiumScene");
		
		SceneManager::CreateScene<TestScene>(L"TestScene");
		
		SceneManager::LoadScene(L"IGStadiumScene");

	}
	void ContentsRelease()
	{
		TGM::Release();
	}
}