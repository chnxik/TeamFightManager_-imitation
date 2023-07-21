#include "sszTestScene.h"
#include "CommonHeader.h"

namespace ssz
{
	using namespace object;

	TestScene::TestScene()
	{
	}

	TestScene::~TestScene()
	{
	}

	void TestScene::Initialize()
	{
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"TestSprite", L"..\\Resources\\useResource\\Sprite\\moderator_ani.png");
		ssz::object::LoadMaterial(L"TestAniMt", L"AnimationShader", L"TestSprite", eRenderingMode::Transparent);

		GameObject* TestObj = Instantiate<GameObject>(Vector3(0.f, 0.f, 1.01f), Vector3(200.f, 200.f, 1.f), eLayerType::Player);
		TestObj->AddComponent<Collider2D>()->Initialize();
		TestObj->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TestAniMt");
		
		Animator* AniComp = TestObj->AddComponent<Animator>();
		AniComp->Create(L"TestAnim", atlas, Vector2(0.f, 96.f), Vector2(32.f, 32.f), 5, Vector2(0.f, 0.f), 1.f / 12.f);
		AniComp->PlayAnimation(L"TestAnim", true);

		// MouseCursor
		{
			GameObject* Cursor = Instantiate<GameObject>(Vector3(0.f, 0.f, 0.01f), Vector3(32.f, 32.f, 1.f), eLayerType::Cursor);
			Cursor->SetName(L"Cursor");
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

	void TestScene::Update()
	{
		Scene::Update();
	}
	void TestScene::LateUpdate()
	{
		Scene::LateUpdate();

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"TitleScene");
		}
	}
	void TestScene::Render()
	{
		Scene::Render();
	}
	void TestScene::OnEnter()
	{
	}
	void TestScene::OnExit()
	{
		CollisionManager::Clear();
	}
}