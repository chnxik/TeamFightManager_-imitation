#include "sszIGStadiumScene.h"
#include "CommonHeader.h"

#include "sszBattleHeader.h"
#include "sszPlayerCardSlot.h"

namespace ssz
{
	using namespace object;

	IGStadiumScene::IGStadiumScene()
	{
	}
	IGStadiumScene::~IGStadiumScene()
	{
	}
	void IGStadiumScene::Initialize()
	{
#pragma region Make Material for this Scene
		{

		}
#pragma endregion
#pragma region Create Object for this Scene
		// GameObject
		{
			// Battle Header
			BattleHeader* BattleHeaderBg = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.019f), eLayerType::UI, L"BattleHeaderBg");

			// PlayerCard
			InstantiateUI<PlayerCardSlot>(Vector3(843.f, 308.f, 1.02f), eLayerType::UI, L"RedPlayerCard_1")->SetRed();
			InstantiateUI<PlayerCardSlot>(Vector3(843.f, 69.f, 1.02f), eLayerType::UI, L"RedPlayerCard_2")->SetRed();
			InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 308.f, 1.02f), eLayerType::UI, L"BluePlayerCard_1")->SetBlue();
			InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 69.f, 1.02f), eLayerType::UI, L"BluePlayerCard_2")->SetBlue();

			// IG Stadium
			GameObject* IG_Stadium = Instantiate<GameObject>(Vector3(0.0f, -139.0f, 1.021f), Vector3(2293.f, 1498.f, 1.f), eLayerType::BackGround);
			IG_Stadium->SetName(L"IG_Stadium");
			IG_Stadium->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumMt");

			// IG StadiumSky
			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.022f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");

			// 오브젝트 배치용 스크립트
			ArrangementScript* ArScript = IG_Stadium->AddComponent<ArrangementScript>();
			ArScript->SetDefault();
		}

		// MouseCursor
		{
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");
			Cursor->AddComponent<CursorScript>()->Initialize();
		}

		// Main Camera
		{
			GameObject* camera = Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.f), eLayerType::Camera);
			camera->SetName(L"MainCamera");
			Camera* cameraComp = camera->AddComponent<Camera>();
		}
#pragma endregion
	}
	void IGStadiumScene::Update()
	{
		Scene::Update();
	}
	void IGStadiumScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void IGStadiumScene::Render()
	{
		Scene::Render();
	}
	void IGStadiumScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void IGStadiumScene::OnExit()
	{
		CollisionManager::Clear();
	}
}