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
		Vector2 vAccel = mForce / mMass;		// ������ ���� ���Է� ���ӵ��� ���Ѵ�.
		mVelocity += vAccel * (float)Time::DeltaTime();

		// ���� ������
		mFriction = 0.1f;
		Vector2 vFriction = -mVelocity;

		if (vFriction != Vector2::Zero)	// �������� 0�� �ƴ� ���
		{
			vFriction.Normalize();	// ����ȭ�� ���⺤�͸� ���Ѵ�.
			vFriction *= mFriction * mFrictionScale * mMass * DT;	// ������ * ������� * �߷� * �ð��ʷ� ������Ʈ
		}

		// �ӵ� ���ҷ�(��ð�¿� ����)�� ���� �ӵ��� �Ѿ� �� ���, ���η� �����.
		if (mVelocity.Length() <= vFriction.Length())
		{
			mVelocity = Vector2::Zero;
		}
		else
		{
			// ���� �ӵ� �ݴ�������� ������ ���� �ӵ� ����
			mVelocity += vFriction;
		}

		// �߷� ���ӵ�
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