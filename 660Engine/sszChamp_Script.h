#pragma once
#include "sszScript.h"
#include "CommonObjHeader.h"

namespace ssz
{
    class Champ_Script : public Script
    {
    public:
        Champ_Script();
        virtual ~Champ_Script();

        virtual void Initialize() override;
        virtual void Update() override;

        virtual void InitChampInfo() = 0;   // 챔프 정보 설정
        virtual void InitChampAnim() = 0;   // 챔프 애니메이션 설정
        virtual void InitColObj() = 0;      // 챔프 콜라이더오브젝트 설정
        virtual void InitBT() = 0;          // 챔프 AI 설정

        virtual void Dead() = 0;

    private:
        Root_Node* mRoot;

    protected:
        Root_Node* CreateRootNode(std::shared_ptr<AIBB> pAIBB)
        {
            mRoot = new Root_Node(pAIBB);
            return mRoot;
        }

        Root_Node* GetRootNode() { return mRoot; }

    };
}