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
		, mResolution(Vector3::Zero)
		, mParent(nullptr)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = (float)(rect.right - rect.left);
		float height = (float)(rect.bottom - rect.top);
		mResolution = { width,height,1.0f };
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

		Matrix scale = Matrix::CreateScale(mScale / Vector3(1000.f, 1000.f, 1.f));

		Matrix rotation;
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position;
		position.Translation(mPosition / mResolution);

		mWorld = scale * rotation * position;

		mUp = Vector3::TransformNormal(Vector3::Up, rotation);
		mForward = Vector3::TransformNormal(Vector3::Forward, rotation);
		mRight = Vector3::TransformNormal(Vector3::Right, rotation);

		if (mParent != nullptr)
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