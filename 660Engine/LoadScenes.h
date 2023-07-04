#pragma once
#include "..\Engine_SOURCE\sszSceneManager.h"
#include "sszTitleScene.h"
#include "sszPrlgScene.h"
#include "sszMainLobbyScene.h"

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

		SceneManager::LoadScene(L"TitleScene");
	}
}