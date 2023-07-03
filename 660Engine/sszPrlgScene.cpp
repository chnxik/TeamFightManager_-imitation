#include "sszPrlgScene.h"

#include "sszInput.h"

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


namespace ssz
{
	PrlgScene::PrlgScene()
		: CutSceneIdx(0)
	{
	}
	PrlgScene::~PrlgScene()
	{
	}
	void PrlgScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Get Using Shader
			std::shared_ptr<Shader> SpriteShader = ssz::Resources::Find<Shader>(L"SpriteShader");

			// Get Using Texture
			std::shared_ptr<Texture> CutScene01Tex = Resources::Load<Texture>(L"CutScene01", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene1.png");
			std::shared_ptr<Texture> CutScene02Tex = Resources::Load<Texture>(L"CutScene02", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene2.png");
			std::shared_ptr<Texture> CutScene03Tex = Resources::Load<Texture>(L"CutScene03", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene3.png");
			std::shared_ptr<Texture> CutScene04Tex = Resources::Load<Texture>(L"CutScene04", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene4.png");
			std::shared_ptr<Texture> CutScene05Tex = Resources::Load<Texture>(L"CutScene05", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene5.png");
			std::shared_ptr<Texture> CutScene06Tex = Resources::Load<Texture>(L"CutScene06", L"..\\Resources\\useResource\\Prlg\\Cutscene\\cutscene6.png");

			// Make Material
			std::shared_ptr<Material> CutScene01_Mt = std::make_shared<Material>();
			CutScene01_Mt->SetShader(SpriteShader);
			CutScene01_Mt->SetTexture(CutScene01Tex);
			CutScene01_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"CutScene01_Mt", CutScene01_Mt);

			std::shared_ptr<Material> CutScene02_Mt = std::make_shared<Material>();
			CutScene02_Mt->SetShader(SpriteShader);
			CutScene02_Mt->SetTexture(CutScene02Tex);
			CutScene02_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"CutScene02_Mt", CutScene02_Mt);

			std::shared_ptr<Material> CutScene03_Mt = std::make_shared<Material>();
			CutScene03_Mt->SetShader(SpriteShader);
			CutScene03_Mt->SetTexture(CutScene03Tex);
			CutScene03_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"CutScene03_Mt", CutScene03_Mt);

			std::shared_ptr<Material> CutScene04_Mt = std::make_shared<Material>();
			CutScene04_Mt->SetShader(SpriteShader);
			CutScene04_Mt->SetTexture(CutScene04Tex);
			CutScene04_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"CutScene04_Mt", CutScene04_Mt);

			std::shared_ptr<Material> CutScene05_Mt = std::make_shared<Material>();
			CutScene05_Mt->SetShader(SpriteShader);
			CutScene05_Mt->SetTexture(CutScene05Tex);
			CutScene05_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"CutScene05_Mt", CutScene05_Mt);

			std::shared_ptr<Material> CutScene06_Mt = std::make_shared<Material>();
			CutScene06_Mt->SetShader(SpriteShader);
			CutScene06_Mt->SetTexture(CutScene06Tex);
			CutScene06_Mt->SetRenderingMode(eRenderingMode::Opaque);
			Resources::Insert(L"CutScene06_Mt", CutScene06_Mt);
		}
#pragma endregion
#pragma region Create Object for this Scene
		// CutScene
		{
			GameObject* CutScene01 = new GameObject();
			CutScene01->SetName(L"CutScene01");
			AddGameObject(eLayerType::Player, CutScene01);

			MeshRenderer* CutScene01_mr = CutScene01->AddComponent<MeshRenderer>();
			CutScene01_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			CutScene01_mr->SetMaterial(Resources::Find<Material>(L"CutScene01_Mt"));
			CutScene01->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.001f));
			CutScene01->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.0f));


			GameObject* CutScene02 = new GameObject();
			CutScene02->SetName(L"CutScene02");
			AddGameObject(eLayerType::Player, CutScene02);

			MeshRenderer* CutScene02_mr = CutScene02->AddComponent<MeshRenderer>();
			CutScene02_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			CutScene02_mr->SetMaterial(Resources::Find<Material>(L"CutScene02_Mt"));
			CutScene02->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.002f));
			CutScene02->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.0f));

			GameObject* CutScene03 = new GameObject();
			CutScene03->SetName(L"CutScene03");
			AddGameObject(eLayerType::Player, CutScene03);

			MeshRenderer* CutScene03_mr = CutScene03->AddComponent<MeshRenderer>();
			CutScene03_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			CutScene03_mr->SetMaterial(Resources::Find<Material>(L"CutScene03_Mt"));
			CutScene03->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.003f));
			CutScene03->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.0f));

			GameObject* CutScene04 = new GameObject();
			CutScene04->SetName(L"CutScene04");
			AddGameObject(eLayerType::Player, CutScene04);

			MeshRenderer* CutScene04_mr = CutScene04->AddComponent<MeshRenderer>();
			CutScene04_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			CutScene04_mr->SetMaterial(Resources::Find<Material>(L"CutScene04_Mt"));
			CutScene04->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.004f));
			CutScene04->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.0f));

			GameObject* CutScene05 = new GameObject();
			CutScene05->SetName(L"CutScene05");
			AddGameObject(eLayerType::Player, CutScene05);

			MeshRenderer* CutScene05_mr = CutScene05->AddComponent<MeshRenderer>();
			CutScene05_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			CutScene05_mr->SetMaterial(Resources::Find<Material>(L"CutScene05_Mt"));
			CutScene05->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.005f));
			CutScene05->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.0f));

			GameObject* CutScene06 = new GameObject();
			CutScene06->SetName(L"CutScene06");
			AddGameObject(eLayerType::Player, CutScene06);

			MeshRenderer* CutScene06_mr = CutScene06->AddComponent<MeshRenderer>();
			CutScene06_mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			CutScene06_mr->SetMaterial(Resources::Find<Material>(L"CutScene06_Mt"));
			CutScene06->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.006f));
			CutScene06->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.0f));

			CutScenes.push_back(CutScene01);
			CutScenes.push_back(CutScene02);
			CutScenes.push_back(CutScene03);
			CutScenes.push_back(CutScene04);
			CutScenes.push_back(CutScene05);
			CutScenes.push_back(CutScene06);
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
#pragma endregion

	}
	void PrlgScene::Update()
	{
		if (5 == CutSceneIdx)
		{
			if (ssz::Input::GetKeyDown(eKeyCode::SPACE))
			{
				// Next Scene
			}
		}
		else if (ssz::Input::GetKeyDown(eKeyCode::SPACE))
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
}
