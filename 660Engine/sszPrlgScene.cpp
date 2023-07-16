#include "sszPrlgScene.h"

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

namespace ssz
{
	using namespace object;

	PrlgScene::PrlgScene()
		: CutSceneIdx(0)
	{
	}
	PrlgScene::~PrlgScene()
	{
	}
	void PrlgScene::Initialize()
	{
		{
			Resources::Load<Texture>(L"CutScene01", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene1.png");
			Resources::Load<Texture>(L"CutScene02", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene2.png");
			Resources::Load<Texture>(L"CutScene03", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene3.png");
			Resources::Load<Texture>(L"CutScene04", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene4.png");
			Resources::Load<Texture>(L"CutScene05", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene5.png");
			Resources::Load<Texture>(L"CutScene06", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene6.png");
		}
		{
			std::shared_ptr<Material> CutScene01_Mt = std::make_shared<Material>();
			CutScene01_Mt->SetMaterial(L"SpriteShader", L"CutScene01", eRenderingMode::Opaque);
			Resources::Insert(L"CutScene01_Mt", CutScene01_Mt);

			std::shared_ptr<Material> CutScene02_Mt = std::make_shared<Material>();
			CutScene02_Mt->SetMaterial(L"SpriteShader", L"CutScene02", eRenderingMode::Opaque);
			Resources::Insert(L"CutScene02_Mt", CutScene02_Mt);

			std::shared_ptr<Material> CutScene03_Mt = std::make_shared<Material>();
			CutScene03_Mt->SetMaterial(L"SpriteShader", L"CutScene03", eRenderingMode::Opaque);
			Resources::Insert(L"CutScene03_Mt", CutScene03_Mt);

			std::shared_ptr<Material> CutScene04_Mt = std::make_shared<Material>();
			CutScene04_Mt->SetMaterial(L"SpriteShader", L"CutScene04", eRenderingMode::Opaque);
			Resources::Insert(L"CutScene04_Mt", CutScene04_Mt);

			std::shared_ptr<Material> CutScene05_Mt = std::make_shared<Material>();
			CutScene05_Mt->SetMaterial(L"SpriteShader", L"CutScene05", eRenderingMode::Opaque);
			Resources::Insert(L"CutScene05_Mt", CutScene05_Mt);

			std::shared_ptr<Material> CutScene06_Mt = std::make_shared<Material>();
			CutScene06_Mt->SetMaterial(L"SpriteShader", L"CutScene06", eRenderingMode::Opaque);
			Resources::Insert(L"CutScene06_Mt", CutScene06_Mt);
		}
#pragma region Create Object for this Scene
		// CutScene
		{
			GameObject* CutScene01 = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.001f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			CutScene01->SetName(L"CutScene01");
			CutScene01->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CutScene01_Mt");

			GameObject* CutScene02 = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.002f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			CutScene02->SetName(L"CutScene02");
			CutScene02->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CutScene02_Mt");

			GameObject* CutScene03 = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.003f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			CutScene03->SetName(L"CutScene03");
			CutScene03->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CutScene03_Mt");

			GameObject* CutScene04 = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.004f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			CutScene04->SetName(L"CutScene04");
			CutScene04->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CutScene04_Mt");

			GameObject* CutScene05 = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.005f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			CutScene05->SetName(L"CutScene05");
			CutScene05->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CutScene05_Mt");

			GameObject* CutScene06 = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.006f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			CutScene06->SetName(L"CutScene06");
			CutScene06->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CutScene06_Mt");

			CutScenes.push_back(CutScene01);
			CutScenes.push_back(CutScene02);
			CutScenes.push_back(CutScene03);
			CutScenes.push_back(CutScene04);
			CutScenes.push_back(CutScene05);
			CutScenes.push_back(CutScene06);
		}

		// MouseCursor
		{
	//		Cursor* CursorObj = Instantiate<Cursor>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
		//	CursorObj->SetName(L"Cursor");
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
	void PrlgScene::Update()
	{
		if (5 == CutSceneIdx)
		{
			if (Input::GetKeyDown(eKeyCode::ENTER))
			{
				// Next Scene
				SceneManager::LoadScene(L"MainLobbyScene");
			}
		}
		else if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			Transform* tf = CutScenes[CutSceneIdx++]->GetComponent<Transform>();
			Vector3 CutScenePos = tf->GetPosition();
			CutScenePos.z = 1.01f;
			tf->SetPosition(CutScenePos);
		}

		Scene::Update();
	}
	void PrlgScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void PrlgScene::Render()
	{
		Scene::Render();
	}
	void PrlgScene::OnEnter()
	{
	}
	void PrlgScene::OnExit()
	{
	}
}
