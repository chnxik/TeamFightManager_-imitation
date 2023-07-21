#pragma once
#include "sszComponent.h"

namespace ssz
{
	class Transform : public Component
	{
	public:
		enum eTransType
		{
			Multiply,
			AddAll,
			PosAdd,
		};

		Transform();
		virtual ~Transform();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Binds() override;

		void SetPosition(Vector3 position) { mPosition = position; }
		void SetRotation(Vector3 rotation) { mRotation = rotation; }
		void SetScale(Vector3 scale) { mScale = scale; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { mScale = Vector3(x, y, z); }
		
		Vector3 GetPosition() { return mPosition;}
		Vector3 GetRotation() { return mRotation;}
		Vector3 GetScale() { return mScale; }

		Vector3 GetWorldPosition() { return mWorldPosition; }
		Vector3 GetWorldRotation() { return mWorldRotation; }
		Vector3 GetWorldScale() { return mWorldScale; }

		Vector3 Forward() { return mForward; }
		Vector3 Right() { return mRight; }
		Vector3 Up() { return mUp; }

		void SetTransType(eTransType eType) { mType = eType; }
		eTransType GetTrasnTyppe() { return mType; }

		GameObject* GetParentOwner() { return mParent->mOwner; }

		void SetParent(Transform* transform) { mParent = transform; }
		Transform* GetParent() { return mParent; }

	private:
		Vector3 mPosition;
		Vector3 mRotation;
		Vector3 mScale;

		Vector3 mWorldPosition;
		Vector3 mWorldRotation;
		Vector3 mWorldScale;

		Vector3 mUp;
		Vector3 mForward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;
		eTransType mType;
	};
}