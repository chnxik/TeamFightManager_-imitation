#include "sszRigidbody.h"

#include "sszGameObject.h"
#include "sszTime.h"
#include "sszTransform.h"

namespace ssz
{
	Rigidbody::Rigidbody()
		: Component(eComponentType::Rigidbody)
		, mForce{}
		, mVelocity{}
		, mMass(0.f)
		, mFriction(0.f)
		, mFrictionScale(0.f)
		, mVelocityLimit(0.f)
		, mGravityLimit(0.f)
		, mGravityAccel(0.f)
		, mTransform(nullptr)
	{
	}
	Rigidbody::~Rigidbody()
	{
	}
	void Rigidbody::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}
	void Rigidbody::Update()
	{
	}
	void Rigidbody::LateUpdate()
	{
		// F = M x A
		Vector2 vAccel = mForce / mMass;		// 더해진 힘과 무게로 가속도를 구한다.
		mVelocity += vAccel * (float)Time::DeltaTime();

		// 공기 마찰력
		mFriction = 0.1f;
		Vector2 vFriction = -mVelocity;

		if (vFriction != Vector2::Zero)	// 마찰력이 0이 아닌 경우
		{
			vFriction.Normalize();	// 정규화로 방향벡터를 구한다.
			vFriction *= mFriction * mFrictionScale * mMass * DT;	// 마찰력 * 마찰계수 * 중력 * 시간초로 업데이트
		}

		// 속도 감소량(마챨력에 의한)이 기존 속도를 넘어 설 경우, 제로로 만든다.
		if (mVelocity.Length() <= vFriction.Length())
		{
			mVelocity = Vector2::Zero;
		}
		else
		{
			// 현재 속도 반대방향으로 마찰에 의한 속도 감소
			mVelocity += vFriction;
		}

		// 중력 가속도
		Vector2 vGravityAccel = Vector2(0.f, mGravityAccel);
		mVelocity += vGravityAccel * DT;

		Vector3 vPos = mTransform->GetPosition();

		vPos.x += mVelocity.x * DT;
		vPos.y += mVelocity.y * DT;

		mTransform->SetPosition(vPos);

		mForce = Vector2::Zero;
	}

	void Rigidbody::Render()
	{
	}

	void Rigidbody::Binds()
	{
	}
}