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

    void UIObject::SetState(eState state)
    {
        GameObject::SetState(state);

        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->SetState(state);
        }
    }

    void UIObject::SetDead()
    {
        GameObject::SetDead();

        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->SetDead();
        }
    }

    void UIObject::SetActive()
    {
        GameObject::SetActive();

        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->SetActive();
        }
    }

    void UIObject::SetPaused()
    {
        GameObject::SetPaused();

        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->SetPaused();
        }
    }

    void UIObject::MouseOnCheck()
    {
        Collider2D* Collider = GetComponent<Collider2D>();
        if (Collider)
        {
            int OverlapCnt = Collider->GetOverlapCnt();

            if(0 < OverlapCnt)
                bMouseOn = true;
            else
                bMouseOn = false;
        }
    }
}