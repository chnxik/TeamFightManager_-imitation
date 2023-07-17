#include "sszPrlgScene.h"
#include "CommonHeader.h"

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
			LoadMaterial(L"CutScene01_Mt", L"SpriteShader", L"CutScene01", eRenderingMode::Opaque);
			LoadMaterial(L"CutScene02_Mt", L"SpriteShader", L"CutScene02", eRenderingMode::Opaque);
			LoadMaterial(L"CutScene03_Mt", L"SpriteShader", L"CutScene03", eRenderingMode::Opaque);
			LoadMaterial(L"CutScene04_Mt", L"SpriteShader", L"CutScene04", eRenderingMode::Opaque);
			LoadMaterial(L"CutScene05_Mt", L"SpriteShader", L"CutScene05", eRenderingMode::Opaque);
			LoadMaterial(L"CutScene06_Mt", L"SpriteShader", L"CutScene06", eRenderingMode::Opaque);
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
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");

			// Init
			Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");
			LoadMaterial(L"CursorMt", L"SpriteShader", L"CursorTex", eRenderingMode::Transparent);

			Cursor->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CursorMt");
			Cursor->AddComponent<Collider2D>()->Initialize();
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
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void PrlgScene::OnExit()
	{
		CollisionManager::Clear();
	}
}
