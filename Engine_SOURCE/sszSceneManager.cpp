#include "sszSceneManager.h"

#include "sszTitleScene.h"

#include "sszPrlgScene1.h"
#include "sszPrlgScene2.h"
#include "sszPrlgScene3.h"

namespace ssz
{
    Scene* SceneManager::mActiveScene = nullptr;
    std::map<std::wstring, Scene*> SceneManager::mScenes;

    void SceneManager::Initialize()
    {
        mActiveScene = new TitleScene();

        Scene* PrlgScene01 = new PrlgScene1();
        Scene* PrlgScene02 = new PrlgScene2();
        Scene* PrlgScene03 = new PrlgScene3();

        mScenes.insert(std::make_pair(L"Title", mActiveScene));

        mScenes.insert(std::make_pair(L"Prlg01", PrlgScene01));
        mScenes.insert(std::make_pair(L"Prlg02", PrlgScene02));
        mScenes.insert(std::make_pair(L"Prlg03", PrlgScene03));
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
            delete iter.second;
            iter.second = nullptr;
        }
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