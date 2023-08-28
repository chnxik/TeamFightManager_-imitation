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
			// GameObjects���� Garbage�� ����ϱ�
			typedef std::vector<GameObject*>::iterator GameObjectIter;
			for (GameObjectIter iter = mGameObjects.begin(); iter != mGameObjects.end();)
			{
				// iter�� Dead�����̴�.
				if ((*iter)->IsDead())
				{
					// Garbage�� �־��ְ� GameObject �迭���� erase �ϱ�.
					mGarbageObjects.push_back(*iter);
					iter = mGameObjects.erase(iter);
				}
				// iter�� Dead���°� �ƴϴ�.
				else
				{
					iter++;
				}
			}
		}

		// ���� �����ӿ��� ������û�� ������Ʈ���� �����ϰ� Garbage�迭�� ����ش�.
		{
			// Garbage�� �ִ� �� ����ó��
			for (GameObject* gameObj : mGarbageObjects)
			{
				delete gameObj;
				gameObj = nullptr;
			}
			// Garbage ���� ����ֱ�
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