#include "sszPlayScene.h"

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
	{
	}

	PlayScene::~PlayScene()
	{
	}

	void PlayScene::Initialize()
	{
		{
			GameObject* player = new GameObject();
			player->SetName(L"player");
			AddGameObject(eLayerType::Player, player);
			
			MeshRenderer* mr = player->AddComponent<MeshRenderer>();
			mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
			mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
			player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 1.0001f));
		}

		// Main Camera
		{
			GameObject* camera = new GameObject();
			AddGameObject(eLayerType::Player, camera);
			camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.0f));
			Camera* cameraComp = camera->AddComponent<Camera>();
			cameraComp->TurnLayerMask(eLayerType::UI, false);
			camera->AddComponent<CameraScript>();
		}

		// UI Camera
		{

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