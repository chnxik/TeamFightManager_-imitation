#include "yaScene.h"
#include "yaPlayer.h"
#include "yaTime.h"

namespace ya
{
	Scene::Scene()
		: acc(0.0f)
		, position(0.0f)
	{
	}
	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
		GameObject* PlayerCicle = new Player();
		PlayerCicle->Initialize();
		((Circle*)PlayerCicle)->CreateCicle(Vector4(0.f, 0.f, 0.1f, 1.0f), Vector4(1.0f, 0.f, 1.0f, 1.0f));

		mGameObjects.push_back(PlayerCicle);
	}

	void Scene::Update()
	{
		acc += ya::Time::DeltaTime();
		if (2.0f < acc)
		{
			acc = acc - 5.0f; // 초기화 후 초과한 시간만큼 더해준다.
			GameObject* Enemy = new Circle();
			Enemy->Initialize();
			((Circle*)Enemy)->CreateCicle(Vector4(position, 0.f, 0.05f, 1.0f), Vector4(1.0f, 1.f, 1.0f, 1.0f));
			position += 0.1f;
		
			mGameObjects.push_back(Enemy);
		}

		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}

	void Scene::LateUpdate()
	{
	}
	void Scene::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}
