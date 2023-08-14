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

        virtual void InitChampInfo() = 0;   // è�� ���� ����
        virtual void InitChampAnim() = 0;   // è�� �ִϸ��̼� ����
        virtual void InitColObj() = 0;      // è�� �ݶ��̴�������Ʈ ����
        virtual void InitBT() = 0;          // è�� AI ����

        virtual void Dead() = 0;

        virtual void Play_Idle() = 0;
        virtual void Play_Move() = 0;
        virtual void Play_Attack() = 0;
        virtual void Play_Dead() = 0;
        virtual void Play_Skill1() = 0;
        virtual void Play_Skill2() = 0;

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