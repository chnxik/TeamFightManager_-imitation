#pragma once
#include "..\Engine_SOURCE\sszSceneManager.h"
#include "sszTitleScene.h"
#include "sszPrlgScene.h"
#include "sszMainLobbyScene.h"
#include "sszStadiumScene.h"
#include "sszBanPickScene.h"
#include "sszIGStadiumScene.h"
#include "sszTestScene.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\x64\\Debug\\660Engine.lib")
#else
#pragma comment(lib, "..\\x64\\Release\\660Engine.lib")
#endif

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

		SceneManager::LoadScene(L"IGStadiumScene");
	}
}