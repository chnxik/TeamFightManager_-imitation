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
        mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<ssz::Transform>();
        mDebugObjects[(UINT)eColliderType::Rect]->AddComponent<ssz::MeshRenderer>()->SetMeshRenderer(L"DebugRect", L"DebugMaterial");
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

    }

    void Editor::Release()
    {
        for (EditorObject* obj : mEditorObjects)
        {
            if (obj != nullptr)
            {
                delete obj;
                obj = nullptr;
            }
        }

        for (DebugObject* obj : mDebugObjects)
        {
            if (obj != nullptr)
            {
                delete obj;
                obj = nullptr;
            }
        }
    }

    void Editor::DebugRender(const ssz::graphics::DebugMesh& mesh)
    {
        DebugObject* debugObj = mDebugObjects[(UINT)mesh.type];

        debugObj->Render();
    }
}