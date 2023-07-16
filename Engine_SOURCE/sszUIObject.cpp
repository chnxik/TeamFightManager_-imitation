#include "sszUIObject.h"
#include "sszCollisionManager.h"

#include "sszInput.h"

namespace ssz
{
    UIObject::UIObject()
        : mParentUI(nullptr)
        , bLbtnDown(false)
        , bMouseOn(false)
        , bOpen(false)
    {
    }

    UIObject::~UIObject()
    {
        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            delete mChildUI[i];
        }
    }

    void UIObject::Initialize()
    {
    }

    void UIObject::Update()
    {
        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->Update();
        }

        GameObject::Update();
    }

    void UIObject::LateUpdate()
    {
        MouseOnCheck();

        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->LateUpdate();
        }

        GameObject::LateUpdate();
    }

    void UIObject::Render()
    {
        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->Render();
        }

        GameObject::Render();
    }

    void UIObject::MouseOnCheck()
    {
        Vector3 Pos = GetComponent<Transform>()->GetWorldPosition();
        Vector3 Scale = GetComponent<Transform>()->GetWorldScale();
        Vector2 MousePos = ssz::Input::GetMousePos();

        if (Pos.x <= MousePos.x && MousePos.x <= Pos.x + Scale.x
            && Pos.y <= MousePos.y && MousePos.y <= Pos.y + Scale.y)
        {
            bMouseOn = true;
        }
        else
        {
            bMouseOn = false;
        }
    }
}