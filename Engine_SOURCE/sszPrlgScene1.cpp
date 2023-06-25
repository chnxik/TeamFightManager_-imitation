#include "sszPrlgScene1.h"

#include "sszSceneManager.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"
#include "sszInput.h"

#include "sszCameraScript.h"

#include "sszResources.h"

namespace ssz
{
    PrlgScene1::PrlgScene1()
    {
        Initialize();
    }

    PrlgScene1::~PrlgScene1()
    {
    }

    void PrlgScene1::Initialize()
    {
        // Title Bg
        GameObject* Bg = new GameObject();
        AddGameObject(eLayerType::BackGround, Bg);
        MeshRenderer* mr = Bg->AddComponent<MeshRenderer>();
        mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
        mr->SetMaterial(Resources::Find<Material>(L"Prlg01BgMaterial"));
        Bg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        Bg->GetComponent<Transform>()->SetScale(Vector3(19.2f / 2.f, 10.8f / 2.f, 0.f));

        // Main Camera
        GameObject* camera = new GameObject();
        AddGameObject(eLayerType::Camera, camera);
        camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
        camera->AddComponent<Camera>();
        camera->AddComponent<CameraScript>();
    }
    void PrlgScene1::Update()
    {
        if (Input::GetKeyDown(eKeyCode::SPACE))
        {
            SceneManager::LoadScene(L"Prlg02");
        }
        Scene::Update();
    }
    void PrlgScene1::LateUpdate()
    {
        Scene::LateUpdate();
    }
    void PrlgScene1::Render()
    {
        Scene::Render();
    }
    void PrlgScene1::OnEnter()
    {
    }
    void PrlgScene1::OnExit()
    {
    }
}