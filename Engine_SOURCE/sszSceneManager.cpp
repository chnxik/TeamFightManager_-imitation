#include "sszSceneManager.h"

namespace ssz
{
    Scene* SceneManager::mActiveScene = nullptr;
    std::map<std::wstring, Scene*> SceneManager::mScenes;

    void SceneManager::Initialize()
    {
    }

    void SceneManager::Update()
    {
        mActiveScene->Update();
    }

    void SceneManager::LateUpdate()
    {
        mActiveScene->LateUpdate();
    }

    void SceneManager::Render()
    {
        mActiveScene->Render();
    }

    void SceneManager::Release()
    {
        for (auto iter : mScenes)
        {
            if (iter.second != nullptr)
            {
                delete iter.second;
                iter.second = nullptr;
            }
        }
    }

    void SceneManager::Destroy()
    {
        mActiveScene->Destroy();
    }

    Scene* SceneManager::LoadScene(std::wstring name)
    {
        std::map<std::wstring, Scene*>::iterator iter
            = mScenes.find(name);

        if (iter == mScenes.end())
            return nullptr;

        mActiveScene->OnExit();
        mActiveScene = iter->second;
        mActiveScene->OnEnter();

        return iter->second;
    }
}