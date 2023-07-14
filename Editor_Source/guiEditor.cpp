#include "guiEditor.h"
#include "..\Engine_SOURCE\sszMesh.h"
#include "..\Engine_SOURCE\sszResources.h"
#include "..\Engine_SOURCE\sszTransform.h"
#include "..\Engine_SOURCE\sszMeshRenderer.h"
#include "..\Engine_SOURCE\sszMaterial.h"
#include "..\Engine_SOURCE\sszRenderer.h"

namespace gui
{
    using namespace ssz::enums;
    std::vector<Widget*> Editor::mWidgets = {};
    std::vector<EditorObject*> Editor::mEditorObjects = {};
    std::vector<DebugObject*> Editor::mDebugObjects = {};

    void Editor::Initialize()
    {
        mDebugObjects.resize((UINT)eColliderType::End);
     
        mDebugObjects[(UINT)eColliderType::Rect] = new DebugObject();
        mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<ssz::MeshRenderer>()->SetMeshRenderer(L"DebugRect", L"DebugMaterial");

        mDebugObjects[(UINT)eColliderType::Circle] = new DebugObject();
        mDebugObjects[(UINT)eColliderType::Circle]->AddComponent<ssz::MeshRenderer>()->SetMeshRenderer(L"DebugCircle", L"DebugMaterial");
    }

    void Editor::Run()
    {
        Update();
        LateUpdate();
        Render();
    }

    void Editor::Update()
    {
        for (EditorObject* obj : mEditorObjects)
        {
            obj->Update();
        }
    }

    void Editor::LateUpdate()
    {
        for (EditorObject* obj : mEditorObjects)
        {
            obj->LateUpdate();
        }
    }

    void Editor::Render()
    {
        for (EditorObject* obj : mEditorObjects)
        {
            obj->Render();
        }

        for (const ssz::graphics::DebugMesh& mesh : renderer::debugMeshs)
        {
            DebugRender(mesh);
        }
        renderer::debugMeshs.clear();
    }

    void Editor::Release()
    {
        for (auto widget : mWidgets)
        {
            delete widget;
            widget = nullptr;
        }

        for (auto editorObj : mEditorObjects)
        {
            delete editorObj;
            editorObj = nullptr;
        }

        for (auto debugObj : mDebugObjects)
        {
            delete debugObj;
            debugObj = nullptr;
        }
    }

    void Editor::DebugRender(const ssz::graphics::DebugMesh& mesh)
    {
        DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

        ssz::Transform* tr = debugObj->GetComponent<ssz::Transform>();

        Vector3 pos = mesh.position;
        pos.z -= 0.01f;

        tr->SetPosition(pos);
        tr->SetScale(mesh.scale);
        tr->SetRotation(mesh.rotation);

        tr->LateUpdate();

        // enum 값으로 DebugMesh에 ColliderType별로 정할 수 있도록 하기. UI이인지 Obj인지

        ssz::Camera* mainCamera = renderer::cameras[0];
        ssz::Camera::SetGpuViewMatrix(mainCamera->GetViewMatrix());
        ssz::Camera::SetGpuProjectionMatrix(mainCamera->GetProjectionMatrix());

        // Collider Line Color CB Bind
        {
            renderer::ColliderCB ColCB = {};
            ColCB.OverlapCnt = mesh.OverlapCnt;

            ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Collider];
            cb->SetData(&ColCB);
            cb->Bind(eShaderStage::PS);
        }

        debugObj->Render();
    }
}