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
		, mLocalPosition(Vector3::Zero)
		, mLocalRotation(Vector3::Zero)
		, mLocalScale(Vector3::One)
		, mWorldPosition(Vector3::Zero)
		, mWorldRotation(Vector3::Zero)
		, mWorldScale(Vector3::One)
		, mParent(nullptr)
		, mTransformType(eTransformType::Default)
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
		if (mParent != nullptr)
		{
			if (eTransformType::Default == mTransformType)
			{
				mWorld = Matrix::Identity;

				Matrix scale = Matrix::CreateScale(mLocalScale);

				Matrix rotation;
				rotation = Matrix::CreateRotationX(mLocalRotation.x);
				rotation *= Matrix::CreateRotationY(mLocalRotation.y);
				rotation *= Matrix::CreateRotationZ(mLocalRotation.z);

				Matrix position;
				position.Translation(mLocalPosition);

				mWorld = scale * rotation * position;

				mUp = Vector3::TransformNormal(Vector3::Up, rotation);
				mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
				mRight = Vector3::TransformNormal(Vector3::Right, rotation);

				mWorld *= mParent->mWorld;
				Quaternion mWorldRot;
				mWorld.Decompose(mWorldScale, mWorldRot, mWorldPosition);
				mWorldRotation = Vector3(mWorldRot.x, mWorldRot.y, mWorldRot.z);
			}
			else if (eTransformType::Add == mTransformType)
			{
				mWorldPosition = mLocalPosition + mParent->mWorldPosition;
				mWorldRotation = mLocalRotation + mParent->mWorldRotation;
				mWorldScale = mLocalScale + mParent->mWorldScale;

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
		}
		else
		{
			mWorldPosition = mLocalPosition;
			mWorldRotation = mLocalRotation;
			mWorldScale = mLocalScale;

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

		std::wstring name = GetOwner()->GetName();
	}

	void Transform::Render()
	{
	}

	void Transform::BindConstantBuffer()
	{
		renderer::TransformCB trCB = {};
		trCB.mWorld = mWorld;
		trCB.mView = Camera::GetViewMatrix();
		trCB.mProjection = Camera::GetProjectionMatrix();

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Transform];
		cb->SetData(&trCB);
		cb->Bind(eShaderStage::VS);
	}
}