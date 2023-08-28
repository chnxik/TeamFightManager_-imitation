#include "sszLayer.h"

namespace ssz
{

	Layer::Layer()
		: mType(eLayerType::End)
	{
	}

	Layer::~Layer()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj == nullptr)
				continue;
		
			delete gameObj;
			gameObj = nullptr;
		}
	}

	void Layer::Initialize()
	{
	}

	void Layer::Update()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if(gameObj->IsActive())
				gameObj->Update();
		}
	}

	void Layer::LateUpdate()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->IsActive())
				gameObj->LateUpdate();
		}
	}

	void Layer::Render()
	{
		for (GameObject* gameObj : mGameObjects)
		{
			if (gameObj->IsActive())
				gameObj->Render();
		}
	}

	void Layer::Destory()
	{
		{
			// GameObjects에서 Garbage에 등록하기
			typedef std::vector<GameObject*>::iterator GameObjectIter;
			for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end();)
			{
				// iter가 Dead상태이다.
				if ((*iter)->IsDead())
				{
					// Garbage에 넣어주고 GameObject 배열에서 erase 하기.
					mGarbageObjects.push_back(*iter);
					iter = mGameObjects.erase(iter);
				}
				// iter가 Dead상태가 아니다.
				else
				{
					iter++;
				}
			}
		}

		// 이전 프레임에서 삭제요청된 오브젝트들을 삭제하고 Garbage배열을 비워준다.
		{
			// Garbage에 있는 것 삭제처리
			for (GameObject* gameObj : mGarbageObjects)
			{
				delete gameObj;
				gameObj = nullptr;
			}
			// Garbage 벡터 비워주기
			mGarbageObjects.clear();
		}
	}

	void Layer::clear()
	{
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		while (iter != mGameObjects.end())
		{
			iter = mGameObjects.erase(iter);
		}
	}

	void Layer::EraseGameObject(GameObject* gameObj)
	{
		std::vector<GameObject*>::iterator iter = mGameObjects.begin();

		while (iter != mGameObjects.end())
		{
			if ((*iter) == gameObj)
			{
				mGameObjects.erase(iter);
				break;
			}

			iter++;
		}
	}

	void Layer::AddGameObject(GameObject* gameObj)
	{
		mGameObjects.push_back(gameObj);
	}
}