#include "sszStadiumScene.h"
#include "CommonHeader.h"

namespace ssz
{
	using namespace object;

	StadiumScene::StadiumScene()
	{
	}
	StadiumScene::~StadiumScene()
	{
	}
	void StadiumScene::Initialize()
	{
		{
			Resources::Load<Texture>(L"StadiumTex", L"..\\Resources\\useResource\\stadium\\stadium_bg.png");
			Resources::Load<Texture>(L"Stadium_ChairTex", L"..\\Resources\\useResource\\stadium\\stadium_chair.png");
			Resources::Load<Texture>(L"Stadium_deskTex", L"..\\Resources\\useResource\\stadium\\stadium_desk.png");
			Resources::Load<Texture>(L"Stadium_frameTex", L"..\\Resources\\useResource\\stadium\\stadium_frame.png");
			Resources::Load<Texture>(L"Stadium_frame_frontTex", L"..\\Resources\\useResource\\stadium\\stadium_frame_front.png");
			Resources::Load<Texture>(L"Stadium_frame_BgTex", L"..\\Resources\\useResource\\stadium\\frame_bg.png");
		}
		{
			std::shared_ptr<Material> Stadium_Mt = std::make_shared<Material>();
			Stadium_Mt->SetMaterial(L"SpriteShader", L"StadiumTex", eRenderingMode::Transparent);
			Resources::Insert(L"StadiumMt", Stadium_Mt);

			std::shared_ptr<Material> Stadium_chair_Mt = std::make_shared<Material>();
			Stadium_chair_Mt->SetMaterial(L"SpriteShader", L"Stadium_ChairTex", eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_chairMt", Stadium_chair_Mt);

			std::shared_ptr<Material> Stadium_desk_Mt = std::make_shared<Material>();
			Stadium_desk_Mt->SetMaterial(L"SpriteShader", L"Stadium_deskTex", eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_deskMt", Stadium_desk_Mt);

			std::shared_ptr<Material> Stadium_frame_Mt = std::make_shared<Material>();
			Stadium_frame_Mt->SetMaterial(L"SpriteShader", L"Stadium_frameTex", eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_frameMt", Stadium_frame_Mt);

			std::shared_ptr<Material> Stadium_frame_front_Mt = std::make_shared<Material>();
			Stadium_frame_front_Mt->SetMaterial(L"SpriteShader", L"Stadium_frame_frontTex", eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_frame_frontMt", Stadium_frame_front_Mt);

			std::shared_ptr<Material> Stadium_frame_Bg_Mt = std::make_shared<Material>();
			Stadium_frame_Bg_Mt->SetMaterial(L"SpriteShader", L"Stadium_frame_BgTex", eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_frame_BgMt", Stadium_frame_Bg_Mt);
		}
#pragma region Create Object for this Scene
		// GameObject
		{
			// StadiumBg
			GameObject* StadiumBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			StadiumBg->SetName(L"StadiumBg");
			StadiumBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"StadiumMt");

			// Stadium Chair
			GameObject* Stadium_Chair = Instantiate<GameObject>(Vector3(0.0f, -115.f, 1.03f), Vector3(1197.f, 143.f, 1.f), eLayerType::BackGround);
			Stadium_Chair->SetName(L"StadiumChair");
			Stadium_Chair->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_chairMt");
			
			 // Stadium Desk
			 GameObject* Stadium_desk = Instantiate<GameObject>(Vector3(0.0f, -147.f, 1.02f), Vector3(1273.f, 141.f, 1.f), eLayerType::BackGround);
			 Stadium_desk->SetName(L"StadiumDesk");
			 Stadium_desk->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_deskMt");
			 
			 // Stadium frame
			 GameObject* Stadium_frame = Instantiate<GameObject>(Vector3(0.0f, -100.f, 1.04f), Vector3(1735.f, 200.f, 1.f), eLayerType::BackGround);
			 Stadium_frame->SetName(L"StadiumFrame");
			 Stadium_frame->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_frameMt");
			 
			 // Stadium frame front
			 GameObject* Stadium_frame_front = Instantiate<GameObject>(Vector3(0.0f, -232.f, 1.01f), Vector3(1768.f, 80.f, 1.f), eLayerType::BackGround);
			 Stadium_frame_front->SetName(L"StadiumFrameFront");
			 Stadium_frame_front->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_frame_frontMt");
			 
			 // Stadium frame Bg
			 GameObject* Stadium_frame_Bg = Instantiate<GameObject>(Vector3(0.0f, -100.f, 1.05f), Vector3(1252.f, 160.f, 1.f), eLayerType::BackGround);
			 Stadium_frame_Bg->SetName(L"StadiumframeBg");
			 Stadium_frame_Bg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"Stadium_frame_BgMt");

			// 오브젝트 배치용 스크립트
			 ArrangementScript* ArScript = Stadium_frame_front->AddComponent<ArrangementScript>();
			 ArScript->SetDefault();
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
	void StadiumScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"BanPickScene");
		}
	}
	void StadiumScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void StadiumScene::Render()
	{
		Scene::Render();
	}
	void StadiumScene::OnEnter()
	{
		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void StadiumScene::OnExit()
	{
		CollisionManager::Clear();
	}
}