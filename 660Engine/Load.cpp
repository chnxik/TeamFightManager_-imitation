#include "Load.h"

#include "CommonHeader.h"

// Scenes
#include "sszTitleScene.h"
// #include "sszPrlgScene.h"
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
		// SceneManager::CreateScene<PrlgScene>(L"PrlgScene");
		SceneManager::CreateScene<MainLobbyScene>(L"MainLobbyScene");
		SceneManager::CreateScene<StadiumScene>(L"StadiumScene");
		SceneManager::CreateScene<BanPickScene>(L"BanPickScene");
		SceneManager::CreateScene<IGStadiumScene>(L"IGStadiumScene");

		SceneManager::CreateScene<TestScene>(L"TestScene");

		SceneManager::LoadScene(L"TestScene");
	}
	void LoadFile()
	{
		std::shared_ptr<File> TestFile = Resources::Load<File>(L"TestFile", L"..\\Resources\\Data\\GameData\\Test.csv");
		// TestFile->DeleteLine();
		wstring szbuff;
		int b = 0;
	
		while (true)
		{
			TestFile->SetData(szbuff, L',');
			TestFile->SetData(b, L',');
			if(TestFile->SetData(b, L'\n') == S_FALSE)
				break;
		}
	}
}