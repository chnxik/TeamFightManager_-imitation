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

        void AddForce(Vector2 vForce) { mForce += vForce; } // Force에 원하는 만큼의 힘을 더한다.
        void SetVelocityLimit(float fLimit) { mVelocityLimit = fLimit; } // 속도 제한 설정
        void SetGrabityVelocityLimit(float fLimit) { mGravityLimit = fLimit; }  // 중력 속도 설정

        void SetVelocity(Vector2 vVelocity) { mVelocity = vVelocity; }  // 속도 직접 설정
        Vector2 GetVelocity() { return mVelocity; } //  현재 설정 반환

        void AddVelocity(Vector2 vAddV) { mVelocity += vAddV; } // 속도 직접 가산


        void SetFriction(float _f) { mFriction = _f; }                                    // 마찰력 설정
        void SetFrictionScale(float _f) { mFrictionScale = _f; }                          // 마찰 계수 설정
        void SetGravityAccel(float fAccel) { mGravityAccel = fAccel; }  // 중력가속도 직접 설정

    private:
        Vector2 mForce;    //  힘
        Vector2 mVelocity; //  속도
        float   mMass;      // 질량

        float   mFriction;          // 마찰력
        float   mFrictionScale;     // 마찰계수

        float   mVelocityLimit; // 제한 속도
        float   mGravityLimit;  // 중력제한속도

        float   mGravityAccel;  // 중력가속도

        Transform* mTransform;  // Owner의 Transform
    };
}