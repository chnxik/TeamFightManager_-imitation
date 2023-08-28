#include "guiEditor.h"
#include "..\Engine_SOURCE\sszMesh.h"
#include "..\Engine_SOURCE\sszResources.h"
#include "..\Engine_SOURCE\sszTransform.h"
#include "..\Engine_SOURCE\sszMeshRenderer.h"
#include "..\Engine_SOURCE\sszMaterial.h"
#include "..\Engine_SOURCE\sszRenderer.h"

#include "..\Engine_SOURCE\sszInput.h"

namespace gui
{
    using namespace ssz::enums;
    std::vector<Widget*> Editor::mWidgets = {};
    std::vector<EditorObject*> Editor::mEditorObjects = {};
    std::vector<DebugObject*> Editor::mDebugObjects = {};

    bool Editor::bDebugOn = false;

    void Editor::Initialize()
    {
        mDebugObjects.resize((UINT)eColliderType::End);
     
        for (UINT etype = 0; etype < (UINT)eColliderType::Sphere; ++etype) // 아직 2가지만 구현
        {
            mDebugObjects[etype] = new DebugObject((eColliderType)etype);
        }
    }

    void Editor::Run()
    {
        Update();
        LateUpdate();
        Render();
    }

    void Editor::Update()
    {
        if (ssz::Input::GetKeyDown(ssz::eKeyCode::F1))
        {
            if(bDebugOn)
                bDebugOn = false;
            else
                bDebugOn = true;
        }

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
        if (bDebugOn)
        {
            for (EditorObject* obj : mEditorObjects)
            {
                obj->Render();
            }

            for (const ssz::graphics::DebugMesh& mesh : renderer::debugMeshs)
            {
                DebugRender(mesh);
            }
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