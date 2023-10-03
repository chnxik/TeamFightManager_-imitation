#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Team;

    class Pilot : public GameObject
    {
    public:
        Pilot();
        virtual ~Pilot();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void CreatePilot(std::wstring Name, UINT ATK, UINT DEF, UINT AGE);

    private:
        // �Ҽ� �� : Team Class�� ������.
        
        // ĳ���� ��� logo (��ü Animator�� ������)
        std::wstring mPilotName;    // �̸�   : wstring
        UINT iPilotATK; // ���ݷ� : UINT
        UINT iPilotDEF; // ���� : UINt
        // ����� : enum class
        
        // è�� ���õ� : struct (����ü�� ������ : è�Ǿ�Key, ��ġ, ����ġ)
        
        UINT iPilotAge; // ����   : UINT
        
        // óġ ( ���� )    // IG ������ 
        // ���� ( ���� )
        // ��� óġ ( ��ü ���� )
        // ��� ���� ( ��ü ���� )

        // ����ϰ��ִ� Champ*
    };
}