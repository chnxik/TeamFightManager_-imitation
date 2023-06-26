#include "sszTitleScene.h"

#include "sszSceneManager.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"
#include "sszInput.h"

#include "sszCameraScript.h"

#include "sszResources.h"


namespace ssz
{
	TitleScene::TitleScene()
	{
		Initialize();
	}
	
	TitleScene::~TitleScene()
	{
	}
	
	void TitleScene::Initialize()
	{
		// Title Bg
		GameObject* Bg = new GameObject();
		AddGameObject(eLayerType::BackGround, Bg);
		MeshRenderer* mr = Bg->AddComponent<MeshRenderer>();
		mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
		mr->SetMaterial(Resources::Find<Material>(L"TitleBgMaterial"));
		Bg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
		Bg->GetComponent<Transform>()->SetScale(Vector3(19.2f/2.f,10.8f/2.f,0.f));

		// Main Camera
		GameObject* camera = new GameObject();
		AddGameObject(eLayerType::Camera, camera);
		camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
		camera->AddComponent<Camera>();
		camera->AddComponent<CameraScript>();
	}
	
	void TitleScene::Update()
	{
		if (Input::GetKeyDown(eKeyCode::SPACE))
		{
			SceneManager::LoadScene(L"Prlg01");
		}
		Scene::Update();
	}
	
	void TitleScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	
	void TitleScene::Render()
	{
		Scene::Render();
	}
	void TitleScene::OnEnter()
	{
	}
	void TitleScene::OnExit()
	{
	}
}