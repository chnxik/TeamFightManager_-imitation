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
			// Get Using Texture
			Resources::Load<Texture>(L"BattleHeaderTex", L"..\\Resources\\useResource\\GameScene\\header_bg.png");

			// Make Material
//			std::shared_ptr<Material> BattleHeader_Mt = std::make_shared<Material>();
//			BattleHeader_Mt->SetShader(SpriteShader);
//			BattleHeader_Mt->SetTexture(BattleHeaderTex);
//			BattleHeader_Mt->SetRenderingMode(eRenderingMode::Transparent);
//			Resources::Insert(L"BattleHeaderMt", BattleHeader_Mt);
		}
#pragma endregion
#pragma region Create Object for this Scene
		// GameObject
		{
			// Battle Header
			GameObject* BattleHeaderBg = new GameObject();
			BattleHeaderBg->SetName(L"BattleHeaderBg");
			AddGameObject(eLayerType::BackGround, BattleHeaderBg);

			MeshRenderer* BattleHeaderBg_mr = BattleHeaderBg->AddComponent<MeshRenderer>();
			BattleHeaderBg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			BattleHeaderBg_mr->SetMaterial(Resources::Find<Material>(L"BattleHeaderMt"));
			BattleHeaderBg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.4785f, 1.04f));
			BattleHeaderBg->GetComponent<Transform>()->SetScale(Vector3(1.92f, 0.123f, 1.f));

			// IG Stadium
			GameObject* IG_Stadium = new GameObject();
			IG_Stadium->SetName(L"Stadium");
			AddGameObject(eLayerType::BackGround, IG_Stadium);

			MeshRenderer* IG_Stadium_Mr = IG_Stadium->AddComponent<MeshRenderer>();
			IG_Stadium_Mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			IG_Stadium_Mr->SetMaterial(Resources::Find<Material>(L"IGStadiumMt"));
			IG_Stadium->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.119f, 1.11f));
			IG_Stadium->GetComponent<Transform>()->SetScale(Vector3(2.235f, 1.46f, 1.f));

			// IG StadiumSky
			GameObject* IG_StadiumSky = new GameObject();
			IG_StadiumSky->SetName(L"StadiumSky");
			AddGameObject(eLayerType::BackGround, IG_StadiumSky);

			MeshRenderer* IG_StadimSky_mr = IG_StadiumSky->AddComponent<MeshRenderer>();
			IG_StadimSky_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			IG_StadimSky_mr->SetMaterial(Resources::Find<Material>(L"IGStadiumSkyMt"));
			IG_StadiumSky->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.136f, 1.12f));
			IG_StadiumSky->GetComponent<Transform>()->SetScale(Vector3(2.144f, 1.429f, 1.f));

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