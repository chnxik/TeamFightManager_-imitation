#include "sszIGStadiumScene.h"

#include "sszInput.h"
#include "sszSceneManager.h"

// Resources
#include "sszResources.h"
#include "sszMaterial.h"
#include "sszMesh.h"

// Component
#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"

// Script
#include "sszArrangementScript.h"
#include "sszCursorScript.h"

// Object
#include "sszObject.h"
#include "sszCursor.h"

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
			GameObject* BattleHeaderBg = Instantiate<GameObject>(Vector3(0.0f, 478.5f, 1.019f), Vector3(1920.f, 123.f, 1.f), eLayerType::BackGround);
			BattleHeaderBg->SetName(L"BattleHeaderBg");
			BattleHeaderBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BattleHeaderMt");

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
			Cursor* CursorObj = Instantiate<Cursor>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			CursorObj->SetName(L"Cursor");
		}

		// Main Camera
		{
			GameObject* camera = Instantiate<GameObject>(Vector3(0.0f, 0.0f, -10.f), eLayerType::UI);
			camera->SetName(L"MainCamera");
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
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
}