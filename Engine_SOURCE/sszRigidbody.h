#pragma once
#include "sszComponent.h"

namespace ssz
{
    class Transform;

    class Rigidbody : public Component
    {
    public:
        Rigidbody();
        virtual ~Rigidbody();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        virtual void Binds();

        void AddForce(Vector2 vForce) { mForce += vForce; } // Force�� ���ϴ� ��ŭ�� ���� ���Ѵ�.
        void SetVelocityLimit(float fLimit) { mVelocityLimit = fLimit; } // �ӵ� ���� ����
        void SetGrabityVelocityLimit(float fLimit) { mGravityLimit = fLimit; }  // �߷� �ӵ� ����

        void SetVelocity(Vector2 vVelocity) { mVelocity = vVelocity; }  // �ӵ� ���� ����
        Vector2 GetVelocity() { return mVelocity; } //  ���� ���� ��ȯ

        void AddVelocity(Vector2 vAddV) { mVelocity += vAddV; } // �ӵ� ���� ����


        void SetFriction(float _f) { mFriction = _f; }                                    // ������ ����
        void SetFrictionScale(float _f) { mFrictionScale = _f; }                          // ���� ��� ����
        void SetGravityAccel(float fAccel) { mGravityAccel = fAccel; }  // �߷°��ӵ� ���� ����

    private:
        Vector2 mForce;    //  ��
        Vector2 mVelocity; //  �ӵ�
        float   mMass;      // ����

        float   mFriction;          // ������
        float   mFrictionScale;     // �������

        float   mVelocityLimit; // ���� �ӵ�
        float   mGravityLimit;  // �߷����Ѽӵ�

        float   mGravityAccel;  // �߷°��ӵ�

        Transform* mTransform;  // Owner�� Transform
    };
}