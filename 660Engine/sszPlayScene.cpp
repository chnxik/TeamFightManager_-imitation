#include "sszPlayScene.h"

#include "sszInput.h"
#include "sszTime.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"

#include "sszResources.h"
#include "sszMesh.h"

#include "sszCameraScript.h"

#include "sszSceneManager.h"

namespace ssz
{
	PlayScene::PlayScene()
		: Title(nullptr)
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		{
			Title = new GameObject();
			Title->SetName(L"player");
			AddGameObject(eLayerType::Player, Title);
			
			MeshRenderer* mr = Title->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			Title->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
			Title->GetComponent<Transform>()->SetScale(Vector3(1.92f, 1.08f, 1.f));
		
			// GameObject* player2 = new GameObject();
			// player2->SetName(L"Child");
			// AddGameObject(eLayerType::Player, player2);
			// 
			// MeshRenderer* mr2 = player2->AddComponent<MeshRenderer>();
			// mr2->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			// mr2->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			// player2->GetComponent<Transform>()->SetPosition(Vector3(1.0f, 0.0f, 1.0001f));
			//  
			// player2->GetComponent<Transform>()->SetParent(player->GetComponent<Transform>()); // player2가 가진 Transform Component의 부모를 player의 Component로 지정한다.
			// 
			// player->GetComponent<Transform>()->SetRotation(Vector3(0.0f, 0.0f, DtoR(180.f)));
		}

		// Main Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"MainCamera");
			AddGameObject(eLayerType::UI, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.15f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);	// UI Layer 는 그리지 않는다.
			camera->AddComponent<CameraScript>();
		}

		// UI Camera
		{
			GameObject* camera = new GameObject();
			camera->SetName(L"UICamera");
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::Player, false); // Player Layer 는 그리지 않는다.
		}
	}

	void PlayScene::Update()
	{
		Scene::Update();
	}

	void PlayScene::LateUpdate()
	{
		Scene::LateUpdate();
	}

	void PlayScene::Render()
	{
		Scene::Render();
	}
}