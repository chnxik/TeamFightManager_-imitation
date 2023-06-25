#include "sszPrlgScene2.h"

#include "sszSceneManager.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"
#include "sszInput.h"

#include "sszCameraScript.h"

#include "sszResources.h"

namespace ssz
{
    PrlgScene2::PrlgScene2()
    {
        Initialize();
    }
    PrlgScene2::~PrlgScene2()
    {
    }
    void PrlgScene2::Initialize()
    {
        // Title Bg
        GameObject* Bg = new GameObject();
        AddGameObject(eLayerType::BackGround, Bg);
        MeshRenderer* mr = Bg->AddComponent<MeshRenderer>();
        mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
        mr->SetMaterial(Resources::Find<Material>(L"Prlg02BgMaterial"));
        Bg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        Bg->GetComponent<Transform>()->SetScale(Vector3(19.2f / 2.f, 10.8f / 2.f, 0.f));

        // Main Camera
        GameObject* camera = new GameObject();
        AddGameObject(eLayerType::Camera, camera);
        camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
        camera->AddComponent<Camera>();
        camera->AddComponent<CameraScript>();
    }
    void PrlgScene2::Update()
    {
        if (Input::GetKeyDown(eKeyCode::SPACE))
        {
            SceneManager::LoadScene(L"Prlg03");
        }
        Scene::Update();
    }
    void PrlgScene2::LateUpdate()
    {
        Scene::LateUpdate();
    }
    void PrlgScene2::Render()
    {
        Scene::Render();
    }
    void PrlgScene2::OnEnter()
    {
    }
    void PrlgScene2::OnExit()
    {
    }
}
