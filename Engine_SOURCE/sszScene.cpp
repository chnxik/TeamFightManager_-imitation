#include "sszScene.h"
#include "sszTime.h"
#include "sszCircle.h"
#include "sszPlayer.h"
#include "sszEnemy.h"

#define SPAWNTIME 1.f

namespace ssz
{
	Scene::Scene()
		: acc(0.0f)
	{
	}

	Scene::~Scene()
	{
	}

	void Scene::Initialize()
	{
		// 여기서 초기 게임 맵데이터를 세팅해줘야 한다.
		srand((unsigned int)time(NULL));

		// Player 생성
		Circle* PlayerCicle = new Player();
		PlayerCicle->SetPos(Vector4(0.f, 0.f, 0.02f, 1.0f));
		PlayerCicle->SetColor(1.0f, 0.f, 1.0f);

		mGameObjects.push_back(PlayerCicle);

		// 초기 Enemy 생성 20개

		for (int i = 0; i < 10; ++i)
		{
			Circle* EnemyCircle = new Enemy();

			float x, y, r, g, b;
			x = (((float)(rand() % 200)) - 100.f) * 0.01f;
			y = (((float)(rand() % 200)) - 100.f) * 0.01f;
			r = (float)(rand() % 11) * 0.1f;
			g = (float)(rand() % 11) * 0.1f;
			b = (float)(rand() % 11) * 0.1f;

			EnemyCircle->SetPos(Vector4(x, y, 0.015f, 1.0f));
			EnemyCircle->SetColor(r, g, b);

			mGameObjects.push_back(EnemyCircle);
		}
	}

	void Scene::Update()
	{
		
		acc += (float)ssz::Time::DeltaTime();
		
		if (SPAWNTIME < acc)
		{
			acc = acc - SPAWNTIME; // 초기화 후 초과한 시간만큼 더해준다.
			Circle* EnemyCircle = new Enemy();
		
			float x, y, r, g, b;
			x = (((float)(rand() % 200)) - 100.f) * 0.01f;
			y = (((float)(rand() % 200)) - 100.f) * 0.01f;
			r = (float)(rand() % 11) * 0.1f;
			g = (float)(rand() % 11) * 0.1f;
			b = (float)(rand() % 11) * 0.1f;

			EnemyCircle->SetPos(Vector4(x, y, 0.015f, 1.0f));
			EnemyCircle->SetColor(r, g, b);
		
			mGameObjects.push_back(EnemyCircle);
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
