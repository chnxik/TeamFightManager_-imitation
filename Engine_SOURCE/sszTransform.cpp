#include "sszTransform.h"
#include "sszRenderer.h"
#include "sszConstantBuffer.h"
#include "sszCamera.h"

namespace ssz
{
	using namespace ssz::graphics;
	Transform::Transform()
		: Component(eComponentType::Tranform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mParent(nullptr)
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

		if (mParent)
		{
			mWorld *= mParent->mWorld;
		}
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