#include "sszSpawnEfc.h"
#include "CommonObjHeader.h"

namespace ssz
{
	SpawnEfc::SpawnEfc()
		: mFront(nullptr)
		, mBack(nullptr)
		, bPlay(false)
	{
	}

	SpawnEfc::~SpawnEfc()
	{
		delete mFront;
		delete mBack;
	}

	void SpawnEfc::Initialize()
	{

		mFront = new GameObject;
		mBack = new GameObject;

		mFront->SetPaused();
		mBack->SetPaused();

		mFront->GetComponent<Transform>()->SetScale(128.f, 128.f, 1.f);
		mBack->GetComponent<Transform>()->SetScale(128.f, 128.f, 1.f);

		SetName(L"Spawn");

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"Spawn_Sprite", L"..\\Resources\\useResource\\ChampSprite\\common\\spawn\\character_spawn_effect.png");
		LoadMaterial(L"SpawnFront_Mt", L"AnimationShader", L"Spawn_Sprite", eRenderingMode::Transparent);
		LoadMaterial(L"SpawnBack_Mt", L"AnimationShader", L"Spawn_Sprite", eRenderingMode::Transparent);

		mFront->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"SpawnFront_Mt");
		mBack->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"SpawnBack_Mt");

		mFront->AddComponent<Animator>();
		mBack->AddComponent<Animator>();

		mFront->GetComponent<Animator>()->Create(L"Spawn_Front", L"Spawn_Sprite", Vector2(0.f, 0.f), Vector2(64.f, 64.f), 11, Vector2(0.f, 0.f), 11.f);
		mFront->GetComponent<Animator>()->CompleteEvent(L"Spawn_Front") = std::bind(&GameObject::SetPaused, mFront);
		mBack->GetComponent<Animator>()->Create(L"Spawn_Back", L"Spawn_Sprite", Vector2(0.f, 64.f), Vector2(64.f, 64.f), 11, Vector2(0.f, 0.f), 11.f);
		mBack->GetComponent<Animator>()->CompleteEvent(L"Spawn_Back") = std::bind(&GameObject::SetPaused, mBack);
	}

	void SpawnEfc::SetLayer()
	{
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, mFront);
		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, mBack);
	}

	void SpawnEfc::Play(Vector3 vPos)
	{
		mFront->GetComponent<Transform>()->SetPosition(Vector3(vPos.x, vPos.y + 10.f, vPos.z - 0.00001f));
		mBack->GetComponent<Transform>()->SetPosition(Vector3(vPos.x, vPos.y + 10.f, vPos.z + 0.00001f));

		mFront->GetComponent<Animator>()->PlayAnimation(L"Spawn_Front", false);
		mBack->GetComponent<Animator>()->PlayAnimation(L"Spawn_Back", false);

		mFront->SetActive();
		mBack->SetActive();

		bPlay = true;
	}
}