#pragma once
#include "sszComponent.h"

namespace ssz
{
	class Transform : public Component
	{
	public:
		enum class eDir
		{
			Left = -1,
			Right = 1,
		};

		enum class eTransType
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
		void SetScale(Vector3 scale) { mFontSize = scale; }

		void SetPosition(float x, float y, float z) { mPosition = Vector3(x, y, z); }
		void SetRotation(float x, float y, float z) { mRotation = Vector3(x, y, z); }
		void SetScale(float x, float y, float z) { mFontSize = Vector3(x, y, z); }

		void AddPosition(float x, float y, float z) { mPosition += Vector3(x, y, z); }
		void AddRotation(float x, float y, float z) { mRotation += Vector3(x, y, z); }
		void AddScale(float x, float y, float z) { mFontSize += Vector3(x, y, z); }
		
		Vector3 GetPosition() { return mPosition;}
		Vector3 GetRotation() { return mRotation;}
		Vector3 GetScale() { return mFontSize; }

		bool IsLeft() { return mDir == eDir::Left; }
		bool IsRight() { return mDir == eDir::Right; }
		void SetLeft() { mDir = eDir::Left; }
		void SetRight() { mDir = eDir::Right; }

		Vector3 GetWorldPosition() { return mWorldPosition; }
		Vector3 GetWorldRotation() { return mWorldRotation; }
		Vector3 GetWorldScale() { return mWorldScale; }

		Vector3 Foward() { return mFoward; }
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
		Vector3 mFontSize;
		eDir	mDir;

		Vector3 mWorldPosition;
		Vector3 mWorldRotation;
		Vector3 mWorldScale;

		Vector3 mUp;
		Vector3 mFoward;
		Vector3 mRight;

		Matrix mWorld;

		Transform* mParent;
		eTransType mType;
	};
}