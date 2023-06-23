#include "sszPlayScene.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"

#include "sszCameraScript.h"

#include "sszResources.h"
#include "sszMesh.h"


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
		// Player Object ¹èÄ¡
		GameObject* player = new GameObject();
		AddGameObject(eLayerType::Player, player);
		MeshRenderer* mr = player->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"SpriteMaterial"));
		player->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));

		// Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Player, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
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