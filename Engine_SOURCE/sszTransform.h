#pragma once
#include "sszComponent.h"

namespace ssz
{
	class Transform : public Component
	{
	public:
		Transform();
		~Transform();

		enum eTransformType
		{
			Default,
			Add,
		};

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void BindConstantBuffer() override;

		void SetLocalPosition(Vector3 position) { mLocalPosition = position; }
		void SetLocalRotation(Vector3 rotation) { mLocalRotation = rotation; }
		void SetLocalScale(Vector3 scale) { mLocalScale = scale; }

		void SetLocalPosition(float x, float y, float z) { mLocalPosition = Vector3(x, y, z); }
		void SetLocalRotation(float x, float y, float z) { mLocalRotation = Vector3(x, y, z); }
		void SetLocalScale(float x, float y, float z) { mLocalScale = Vector3(x, y, z); }
		
		void SetDefaultType() { mTransformType = eTransformType::Default; }
		void SetAddType() { mTransformType = eTransformType::Add; }

		Vector3 GetLocalPosition() { return mLocalPosition;}
		Vector3 GetLocalRotation() { return mLocalRotation;}
		Vector3 GetLocalScale() { return mLocalScale; }

		Vector3 GetWorldPosition() { return mWorldPosition; }
		Vector3 GetWorldRotation() { return mWorldRotation; }
		Vector3 GetWorldScale() { return mWorldScale; }

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		GameObject* GetParentOwner() { return mParent->mOwner; }
		template <typename T>
		T* GetParentComponent() { return mParent->mOwner->GetComponent<T>(); }

		void SetParent(Transform* transform) { mParent = transform; }
		Transform* GetParent() { return mParent; }

	private:
		Vector3 mLocalPosition;
		Vector3 mLocalRotation;
		Vector3 mLocalScale;

		Vector3 mWorldPosition;
		Vector3 mWorldRotation;
		Vector3 mWorldScale;

		Vector3 mUp;
		Vector3 mForward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;

		eTransformType mTransformType;
	};
}