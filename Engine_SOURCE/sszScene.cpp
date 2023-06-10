#include "sszScene.h"
#include "sszTime.h"
#include "sszCircle.h"
#include "sszPlayer.h"
#include "sszEnemy.h"

#define SPAWNTIME 0.1f

namespace ssz
{
	Scene::Scene()
		: mPlayer(nullptr)
		, acc(0.0f)
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
		mPlayer = new Player();
		((Circle*)mPlayer)->SetPos(Vector4(0.f, 0.f, 0.02f, 1.0f));
		((Circle*)mPlayer)->SetColor(1.0f, 0.f, 1.0f);

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

		mPlayer->Update();
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Update();
		}
	}

	void Scene::LateUpdate()
	{
		int deleteCnt;

		deleteCnt = 0;

		Vector4 PlayerPos = ((Circle*)mPlayer)->GetPos();
		Vector4 EnemyPos = {};
		float dist = 0.f;
		float contactdist = 0.f;
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		// 충돌 검사
		for (GameObject* gameObj : mGameObjects)
		{
			
			EnemyPos = ((Circle*)gameObj)->GetPos();	// Enemy Pos
			contactdist = PlayerPos.z + EnemyPos.z;		// 접촉 거리 ( 두 개체 반지름 합계 )

			// 거리판단
			dist = sqrt((PlayerPos.x - EnemyPos.x) * (PlayerPos.x - EnemyPos.x) + (PlayerPos.y - EnemyPos.y) * (PlayerPos.y - EnemyPos.y));


			// 충돌했을 때
			if (dist < contactdist)
			{
				iter = mGameObjects.erase(iter);	// 충돌한 적 객체 제거
				PlayerPos.z += 0.001f;				// 플레이어 크기 증가
				
				((Circle*)mPlayer)->SetPos(PlayerPos);	// 증가한 크기 반영
			}

			// 충돌하지 않았으나 근처에 있을 때
			else if (dist < contactdist + 0.05f)
			{
				if (!((Enemy*)gameObj)->IsMagnet())
				{
					((Enemy*)gameObj)->SetMagnet((Circle*)mPlayer);
				}
				iter++;
			}

			// 충돌하지 않았을 때
			else
			{
				iter++;
			}
		}
		
	}
	void Scene::Render()
	{
		mPlayer->Render();
		for (GameObject* gameObj : mGameObjects)
		{
			gameObj->Render();
		}
	}
}
