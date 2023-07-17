#include "Load.h"

#include "sszSceneManager.h"

// Scenes
#include "sszTitleScene.h"
#include "sszPrlgScene.h"
#include "sszMainLobbyScene.h"
#include "sszStadiumScene.h"
#include "sszBanPickScene.h"
#include "sszIGStadiumScene.h"
#include "sszTestScene.h"

namespace ssz
{
	void InitializeScenes()
	{
		SceneManager::CreateScene<TitleScene>(L"TitleScene");
		SceneManager::CreateScene<PrlgScene>(L"PrlgScene");
		SceneManager::CreateScene<MainLobbyScene>(L"MainLobbyScene");
		SceneManager::CreateScene<StadiumScene>(L"StadiumScene");
		SceneManager::CreateScene<BanPickScene>(L"BanPickScene");
		SceneManager::CreateScene<IGStadiumScene>(L"IGStadiumScene");

		// SceneManager::CreateScene<TestScene>(L"TestScene");

		SceneManager::LoadScene(L"TitleScene");
	}
}