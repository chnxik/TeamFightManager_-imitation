#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class Pilot : public GameObject
    {
    public:
        Pilot();
        virtual ~Pilot();

    private:
        // �Ҽ� �� : Team Class�� ������.
        
        // ĳ���� ��� logo (��ü Animator�� ������)
        // �̸�   : wstring
        // ���ݷ� : UINT
        // ���� : UINt
        // ����� : enum class
        
        // è�� ���õ� : struct (����ü�� ������ : è�Ǿ�Key, ��ġ, ����ġ)
        
        // ����   : UINT
        // ������� : UINT
        // ���� ��� : UINT
        
        // óġ ( ���� )    // IG ������ 
        // ���� ( ���� )
        // ��� óġ ( ��ü ���� )
        // ��� ���� ( ��ü ���� )

        // ����ϰ��ִ� Champ*
    };
}