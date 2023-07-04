#include "sszStadiumScene.h"

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

namespace ssz
{
	StadiumScene::StadiumScene()
	{
	}
	StadiumScene::~StadiumScene()
	{
	}
	void StadiumScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Get Using Shader
			std::shared_ptr<Shader> SpriteShader = ssz::Resources::Find<Shader>(L"SpriteShader");

			// Get Using Texture
			std::shared_ptr<Texture> StadiumTex = Resources::Load<Texture>(L"Stadium", L"..\\Resources\\useResource\\stadium\\stadium_bg.png");
			std::shared_ptr<Texture> Stadium_ChairTex = Resources::Load<Texture>(L"Stadium_Chair", L"..\\Resources\\useResource\\stadium\\stadium_chair.png");
			std::shared_ptr<Texture> Stadium_deskTex = Resources::Load<Texture>(L"Stadium_desk", L"..\\Resources\\useResource\\stadium\\stadium_desk.png");
			std::shared_ptr<Texture> Stadium_frameTex = Resources::Load<Texture>(L"Stadium_frame", L"..\\Resources\\useResource\\stadium\\stadium_frame.png");
			std::shared_ptr<Texture> Stadium_frame_frontTex = Resources::Load<Texture>(L"Stadium_frame_front", L"..\\Resources\\useResource\\stadium\\stadium_frame_front.png");
			std::shared_ptr<Texture> Stadium_frame_BgTex = Resources::Load<Texture>(L"Stadium_frame_Bg", L"..\\Resources\\useResource\\stadium\\frame_bg.png");

			// Mouse Cursor Tex
			std::shared_ptr<Texture> CursorTex = Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			// Make Material
			std::shared_ptr<Material> Stadium_Mt = std::make_shared<Material>();
			Stadium_Mt->SetShader(SpriteShader);
			Stadium_Mt->SetTexture(StadiumTex);
			Stadium_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"StadiumMt", Stadium_Mt);

			std::shared_ptr<Material> Stadium_chair_Mt = std::make_shared<Material>();
			Stadium_chair_Mt->SetShader(SpriteShader);
			Stadium_chair_Mt->SetTexture(Stadium_ChairTex);
			Stadium_chair_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_chairMt", Stadium_chair_Mt);

			std::shared_ptr<Material> Stadium_desk_Mt = std::make_shared<Material>();
			Stadium_desk_Mt->SetShader(SpriteShader);
			Stadium_desk_Mt->SetTexture(Stadium_deskTex);
			Stadium_desk_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_deskMt", Stadium_desk_Mt);

			std::shared_ptr<Material> Stadium_frame_Mt = std::make_shared<Material>();
			Stadium_frame_Mt->SetShader(SpriteShader);
			Stadium_frame_Mt->SetTexture(Stadium_frameTex);
			Stadium_frame_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_frameMt", Stadium_frame_Mt);

			std::shared_ptr<Material> Stadium_frame_front_Mt = std::make_shared<Material>();
			Stadium_frame_front_Mt->SetShader(SpriteShader);
			Stadium_frame_front_Mt->SetTexture(Stadium_frame_frontTex);
			Stadium_frame_front_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_frame_frontMt", Stadium_frame_front_Mt);

			std::shared_ptr<Material> Stadium_frame_Bg_Mt = std::make_shared<Material>();
			Stadium_frame_Bg_Mt->SetShader(SpriteShader);
			Stadium_frame_Bg_Mt->SetTexture(Stadium_frame_BgTex);
			Stadium_frame_Bg_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"Stadium_frame_BgMt", Stadium_frame_Bg_Mt);


			// Mouse Cursor Material
			std::shared_ptr<Material> Cursor_Mt = std::make_shared<Material>();
			Cursor_Mt->SetShader(SpriteShader);
			Cursor_Mt->SetTexture(CursorTex);
			Cursor_Mt->SetRenderingMode(eRenderingMode::Transparent);
			Resources::Insert(L"CursorMt", Cursor_Mt);


		}
#pragma endregion
#pragma region Create Object for this Scene
		// GameObject
		{
			// StadiumBg
			GameObject* StadiumBg = new GameObject();
			StadiumBg->SetName(L"StadiumBg");
			AddGameObject(eLayerType::BackGround, StadiumBg);

			MeshRenderer* StadiumBg_mr = StadiumBg->AddComponent<MeshRenderer>();
			StadiumBg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			StadiumBg_mr->SetMaterial(Resources::Find<Material>(L"StadiumMt"));
			StadiumBg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.1f));
			StadiumBg->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.f));

			// Stadium Chair
			GameObject* Stadium_Chair = new GameObject();
			Stadium_Chair->SetName(L"StadiumChair");
			AddGameObject(eLayerType::BackGround, Stadium_Chair);
			
			MeshRenderer* Stadium_Chair_mr = Stadium_Chair->AddComponent<MeshRenderer>();
			Stadium_Chair_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Stadium_Chair_mr->SetMaterial(Resources::Find<Material>(L"Stadium_chairMt"));
			Stadium_Chair->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.115f, 1.03f));
			Stadium_Chair->GetComponent<Transform>()->SetScale(Vector3(1.197f, 0.143f, 1.f));
			
			 // Stadium Desk
			 GameObject* Stadium_desk = new GameObject();
			 Stadium_desk->SetName(L"StadiumDesk");
			 AddGameObject(eLayerType::BackGround, Stadium_desk);
			 
			 MeshRenderer* Stadium_desk_mr = Stadium_desk->AddComponent<MeshRenderer>();
			 Stadium_desk_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			 Stadium_desk_mr->SetMaterial(Resources::Find<Material>(L"Stadium_deskMt"));
			 Stadium_desk->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.143f, 1.02f));
			 Stadium_desk->GetComponent<Transform>()->SetScale(Vector3(1.273f, 0.141f, 1.f));
			 
			 // Stadium frame
			 GameObject* Stadium_frame = new GameObject();
			 Stadium_frame->SetName(L"StadiumFrame");
			 AddGameObject(eLayerType::BackGround, Stadium_frame);
			 
			 MeshRenderer* Stadium_frame_mr = Stadium_frame->AddComponent<MeshRenderer>();
			 Stadium_frame_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			 Stadium_frame_mr->SetMaterial(Resources::Find<Material>(L"Stadium_frameMt"));
			 Stadium_frame->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.1f, 1.04f));
			 Stadium_frame->GetComponent<Transform>()->SetScale(Vector3(1.7352f, 0.2f, 1.f));
			 
			 // Stadium frame front
			 GameObject* Stadium_frame_front = new GameObject();
			 Stadium_frame_front->SetName(L"StadiumFrameFront");
			 AddGameObject(eLayerType::BackGround, Stadium_frame_front);
			 
			 MeshRenderer* Stadium_frame_front_mr = Stadium_frame_front->AddComponent<MeshRenderer>();
			 Stadium_frame_front_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			 Stadium_frame_front_mr->SetMaterial(Resources::Find<Material>(L"Stadium_frame_frontMt"));
			 Stadium_frame_front->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.232f, 1.01f));
			 Stadium_frame_front->GetComponent<Transform>()->SetScale(Vector3(1.768f, 0.08f, 1.f));

			 // Stadium frame Bg
			 GameObject* Stadium_frame_Bg = new GameObject();
			 Stadium_frame_Bg->SetName(L"StadiumframeBg");
			 AddGameObject(eLayerType::BackGround, Stadium_frame_Bg);

			 MeshRenderer* Stadium_frame_Bg_mr = Stadium_frame_Bg->AddComponent<MeshRenderer>();
			 Stadium_frame_Bg_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			 Stadium_frame_Bg_mr->SetMaterial(Resources::Find<Material>(L"Stadium_frame_BgMt"));
			 Stadium_frame_Bg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, -0.1f, 1.05f));
			 Stadium_frame_Bg->GetComponent<Transform>()->SetScale(Vector3(1.252f, 0.16f, 1.f));

			// 오브젝트 배치용 스크립트
			// ArrangementScript* ArScript = Stadium_frame_Bg->AddComponent<ArrangementScript>();
			// ArScript->SetDefault();
		}

		// MouseCursor
		{
			GameObject* Cursor = new GameObject();
			Cursor->SetName(L"Cursor");
			AddGameObject(eLayerType::Cursor, Cursor);

			MeshRenderer* Cursor_mr = Cursor->AddComponent<MeshRenderer>();
			Cursor_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			Cursor_mr->SetMaterial(Resources::Find<Material>(L"CursorMt"));
			Cursor->GetComponent<Transform>()->SetPosition(Vector3(-0.9f, 0.0f, 0.01f));
			Cursor->GetComponent<Transform>()->SetScale(Vector3(0.032f, 0.032f, 1.0f));
			Cursor->AddComponent<CursorScript>();
		}

		// Main Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"MainCamera");
			AddGameObject(eLayerType::UI, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
		}


		// UI Camera
		{
			GameObject* UIcamera = new GameObject();
			UIcamera->SetName(L"UICamera");
			AddGameObject(eLayerType::UI, UIcamera);
			UIcamera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
			Camera* cameraComp = UIcamera->AddComponent<Camera>();
			cameraComp->DisableLayerMasks();
			cameraComp->TurnLayerMask(eLayerType::UI, true);
			cameraComp->TurnLayerMask(eLayerType::Cursor, true);
		}
#pragma endregion
	}
	void StadiumScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::LBUTTON))
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
}