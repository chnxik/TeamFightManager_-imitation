#include "sszUIObject.h"
#include "sszCollisionManager.h"
#include "sszInput.h"

#include "sszUIComponent.h"
#include "sszButtonUI.h"

namespace ssz
{
    UIObject::UIObject()
        : mParentUI(nullptr)
        , bLbtnDown(false)
        , bMouseOn(false)
        , bOpen(false)
    {
    }
    UIObject::UIObject(const std::wstring& Key)
        : mUIKey(Key)
        , mParentUI(nullptr)
        , bLbtnDown(false)
        , bMouseOn(false)
        , bOpen(false)
    {
        SetName(mUIKey);
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

    void UIObject::RegistRespawnPool()
    {
        GameObject::RegistRespawnPool();

        for (size_t i = 0; i < mChildUI.size(); ++i)
        {
            mChildUI[i]->RegistRespawnPool();
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

    void UIObject::MouseLbtnDown()
    {
        bLbtnDown = true;

        std::vector<UIComponent*> UIComponents = GetComponents<UIComponent>();

        for (UIComponent* UIComp : UIComponents)
        {
            UIComp->MouseLbtnDown();
        }
    }

    void UIObject::MouseLbtnUp()
    {
        bLbtnDown = false;

        std::vector<UIComponent*> UIComponents = GetComponents<UIComponent>();

        for (UIComponent* UIComp : UIComponents)
        {
            UIComp->MouseLbtnUp();
        }
    }

    void UIObject::MouseLbtnClicked()
    {
        std::vector<UIComponent*> UIComponents = GetComponents<UIComponent>();

        for (UIComponent* UIComp : UIComponents)
        {
            UIComp->MouseLbtnClicked();
        }
    }

    void UIObject::MouseOn()
    {
        std::vector<UIComponent*> UIComponents = GetComponents<UIComponent>();

        for (UIComponent* UIComp : UIComponents)
        {
            UIComp->MouseOn();
        }
    }

    void UIObject::MouseOnCheck()
    {
        // 충돌체 확인 방식
        /*
        Collider2D* Collider = GetComponent<Collider2D>();
        if (Collider)
        {
            int OverlapCnt = Collider->GetOverlapCnt();

            if(0 < OverlapCnt)
                bMouseOn = true;
            else
            {
                bMouseOn = false;
            }
        }
        */

        // 좌표 확인 방식
        
        /*
        if (vPos.x <= vMousePos.x && vMousePos.x <= vPos.x + vScale.x
            && vPos.y <= vMousePos.y && vMousePos.y <= vPos.y + vScale.y)
        {
            if (!m_bMouseOn)
                CCsrMgr::GetInst()->AddCsrOnCnt();

            m_bMouseOn = true;
        }
        else
        {
            if (m_bMouseOn)
                CCsrMgr::GetInst()->SubCsrOnCnt();

            m_bMouseOn = false;
        }
        */

        // 사각 원 혼합 충돌 : OBB 응용
        {
            Collider2D* UICol = GetComponent<Collider2D>();

            Vector3 UIPos = UICol->GetColliderPos();
            Vector3 UIScale = UICol->GetColliderScale();

            Vector3 MousePos = Input::GetMousePos4DX();
            Vector3 MouseScale = Vector3::One;

            Vector3 CenterDir = UIPos - MousePos; // 두 객체의 중심끼리의 거리벡터
            Vector3 Axis; // 기준 투영축
            float CenterProjDist; // 투영축 기준으로 두 중심점 사이의 거리 스칼라
            float r1, r2; // 비교 대상인 두 벡터의 투영길이


            //  1. Rect의 right축 투영
            Axis = UICol->GetAxis(Collider2D::eAxis::Right);
            CenterProjDist = abs(CenterDir.Dot(Axis));

            r1 = UIScale.x / 2.f;
            r2 = MouseScale.x / 2.f;

            if (r1 + r2 < CenterProjDist)
            {
                bMouseOn = false;
                return;
            }
            
            // 2. Rect의 up축 투영
            Axis = UICol->GetAxis(Collider2D::eAxis::Up);
            CenterProjDist = abs(CenterDir.Dot(Axis));

            r1 = UIScale.y / 2.f;
            r2 = MouseScale.y / 2.f;

            if (r1 + r2 < CenterProjDist)
            {
                bMouseOn = false;
                return;
            }


            // 3. Circle기준 right축 투영
            Axis = Vector3::UnitX;
            CenterProjDist = abs(CenterDir.Dot(Axis));

            r1 = MouseScale.x / 2.f;
            r2 = UICol->GetLength4OBB(Axis);

            if (r1 + r2 < CenterProjDist)
            {
                bMouseOn = false;
                return;
            }

            // 4. Circle기준 up축 투영
            Axis = Vector3::UnitY;
            CenterProjDist = abs(CenterDir.Dot(Axis));

            r1 = MouseScale.y / 2.f;
            r2 = UICol->GetLength4OBB(Axis);

            if (r1 + r2 < CenterProjDist)
            {
                bMouseOn = false;
                return;
            }

            bMouseOn = true;
        }
    }
}