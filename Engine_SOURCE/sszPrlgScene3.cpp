#include "sszPrlgScene3.h"

#include "sszSceneManager.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"
#include "sszInput.h"

#include "sszCameraScript.h"

#include "sszResources.h"

namespace ssz
{
    PrlgScene3::PrlgScene3()
    {
        Initialize();
    }
    PrlgScene3::~PrlgScene3()
    {
    }
    void PrlgScene3::Initialize()
    {
        // Title Bg
        GameObject* Bg = new GameObject();
        AddGameObject(eLayerType::BackGround, Bg);
        MeshRenderer* mr = Bg->AddComponent<MeshRenderer>();
        mr->SetMesh(Resources::Find<Mesh>(L"RectMesh"));
        mr->SetMaterial(Resources::Find<Material>(L"Prlg03BgMaterial"));
        Bg->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, 0.0f));
        Bg->GetComponent<Transform>()->SetScale(Vector3(19.2f / 2.f, 10.8f / 2.f, 0.f));

        // Main Camera
        GameObject* camera = new GameObject();
        AddGameObject(eLayerType::Camera, camera);
        camera->GetComponent<Transform>()->SetPosition(Vector3(0.0f, 0.0f, -10.f));
        camera->AddComponent<Camera>();
        camera->AddComponent<CameraScript>();
    }
    void PrlgScene3::Update()
    {
        if (Input::GetKeyDown(eKeyCode::SPACE))
        {
            SceneManager::LoadScene(L"Title");
        }
        Scene::Update();
    }
    void PrlgScene3::LateUpdate()
    {
        Scene::LateUpdate();
    }
    void PrlgScene3::Render()
    {
        Scene::Render();
    }
    void PrlgScene3::OnEnter()
    {
    }
    void PrlgScene3::OnExit()
    {
    }
}
