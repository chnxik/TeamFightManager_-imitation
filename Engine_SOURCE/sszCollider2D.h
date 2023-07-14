#pragma once
#include "sszComponent.h"
#include "sszTransform.h"

namespace ssz
{
	class Collider2D : public Component
	{
	public:
		Collider2D();
		~Collider2D();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void BindConstantBuffer() override;

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);
		
		void SetType(eColliderType type) { mType = type; }
		void SetOffsetSize(Vector3 size) { mOffsetScale = size; }
		void SetOffsetPos(Vector3 pos) { mOffsetPosition = pos; }

		Vector3 GetColliderScale() { return mFinalScale; }
		Vector3 GetColliderPos() { return mFinalPos; }
		Vector3 GetColliderRotation() { return mFinalRotation; }
		
		UINT GetColliderID() { return mColliderID; }
		eColliderType GetType() { return mType; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector3 mOffsetScale;
		Vector3 mOffsetPosition;

		Vector3 mFinalScale;
		Vector3 mFinalPos;
		Vector3 mFinalRotation;

		int mOverlapCnt;
	};
}