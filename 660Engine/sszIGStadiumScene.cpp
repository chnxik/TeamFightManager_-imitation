#include "sszIGStadiumScene.h"
#include "CommonHeader.h"

#include "sszObj_IG_Stadium.h"

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
			IG_Stadium* Stadium = Instantiate<IG_Stadium>(Vector3(0.0f, -139.0f, 1.021f), Vector3(2293.f, 1498.f, 1.f), eLayerType::BackGroundObj);

			// IG StadiumSky
			GameObject* IG_StadiumSky = Instantiate<GameObject>(Vector3(0.0f, -53.0f, 1.022f), Vector3(2144.f, 1429.f, 1.f), eLayerType::BackGround);
			IG_StadiumSky->SetName(L"IG_StadiumSky");
			IG_StadiumSky->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumSkyMt");
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
		Cursor::RegistCursor(this);
		MainCamera::RegistCamera(this);

		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void IGStadiumScene::OnExit()
	{
		CollisionManager::Clear();

		Erase(eLayerType::Cursor);
		Erase(eLayerType::Camera);
	}
}