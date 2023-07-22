#include "sszTransform.h"
#include "sszRenderer.h"
#include "sszConstantBuffer.h"
#include "sszCamera.h"
#include "sszApplication.h"

extern ssz::Application application;

namespace ssz
{
	using namespace ssz::graphics;
	Transform::Transform()
		: Component(eComponentType::Tranform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mDir(eDir::Right)
		, mWorldPosition(Vector3::Zero)
		, mWorldRotation(Vector3::Zero)
		, mWorldScale(Vector3::One)
		, mParent(nullptr)
		, mType(eTransType::Multiply)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::Initialize()
	{
	}

	void Transform::Update()
	{
	}

	void Transform::LateUpdate()
	{
		if (mParent)
		{
			switch (mType)
			{
			case ssz::Transform::eTransType::Multiply:
			{
				mWorld = Matrix::Identity;

				Matrix scale = Matrix::CreateScale(mScale);

				Matrix rotation;
				rotation = Matrix::CreateRotationX(mRotation.x);
				rotation *= Matrix::CreateRotationY(mRotation.y);
				rotation *= Matrix::CreateRotationZ(mRotation.z);

				Matrix position;
				position.Translation(mPosition);

				mWorld = scale * rotation * position;

				mUp = Vector3::TransformNormal(Vector3::Up, rotation);
				mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
				mRight = Vector3::TransformNormal(Vector3::Right, rotation);

				mWorld *= mParent->mWorld;
				Quaternion tmp;
				mWorld.Decompose(mWorldScale, tmp, mWorldPosition);
				mWorldRotation = mRotation + mParent->mWorldRotation; // Rotation은 합으로 계산
			}
				break;
			case ssz::Transform::eTransType::AddAll:
			{
				mWorldPosition = mPosition + mParent->mWorldPosition;
				mWorldRotation = mRotation + mParent->mWorldRotation;
				mWorldScale = mScale + mParent->mWorldScale;

				mWorld = Matrix::Identity;

				Matrix scale = Matrix::CreateScale(mWorldScale);

				Matrix rotation;
				rotation = Matrix::CreateRotationX(mWorldRotation.x);
				rotation *= Matrix::CreateRotationY(mWorldRotation.y);
				rotation *= Matrix::CreateRotationZ(mWorldRotation.z);

				Matrix position;
				position.Translation(mWorldPosition);

				mWorld = scale * rotation * position;

				mUp = Vector3::TransformNormal(Vector3::Up, rotation);
				mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
				mRight = Vector3::TransformNormal(Vector3::Right, rotation);
			}
				break;
			case ssz::Transform::eTransType::PosAdd:
			{
				mWorldPosition = mPosition + mParent->mWorldPosition;
				mWorldRotation = mRotation + mParent->mWorldRotation;
				mWorldScale = mScale;

				mWorld = Matrix::Identity;

				Matrix scale = Matrix::CreateScale(mWorldScale);

				Matrix rotation;
				rotation = Matrix::CreateRotationX(mWorldRotation.x);
				rotation *= Matrix::CreateRotationY(mWorldRotation.y);
				rotation *= Matrix::CreateRotationZ(mWorldRotation.z);

				Matrix position;
				position.Translation(mWorldPosition);

				mWorld = scale * rotation * position;

				mUp = Vector3::TransformNormal(Vector3::Up, rotation);
				mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
				mRight = Vector3::TransformNormal(Vector3::Right, rotation);
			}
				break;
			default:
				break;
			}
		}
		else
		{
			mWorld = Matrix::Identity;

			Matrix scale = Matrix::CreateScale(mScale);

			Matrix rotation;
			rotation = Matrix::CreateRotationX(mRotation.x);
			rotation *= Matrix::CreateRotationY(mRotation.y);
			rotation *= Matrix::CreateRotationZ(mRotation.z);

			Matrix position;
			position.Translation(mPosition);

			mWorld = scale * rotation * position;

			mUp = Vector3::TransformNormal(Vector3::Up, rotation);
			mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
			mRight = Vector3::TransformNormal(Vector3::Right, rotation);

			mWorldPosition = mPosition;
			mWorldRotation = mRotation;
			mWorldScale = mScale;
		}
	}

	void Transform::Render()
	{
	}

	void Transform::Binds()
	{
		renderer::TransformCB trCB = {};
		trCB.mWorld = mWorld;
		trCB.mView = Camera::GetGpuViewMatrix();
		trCB.mProjection = Camera::GetGpuProjectionMatrix();
		trCB.mDir = (float)mDir;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
}