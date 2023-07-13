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

		void OnCollisionEnter(Collider2D* other);
		void OnCollisionStay(Collider2D* other);
		void OnCollisionExit(Collider2D* other);
		
		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mOffsetScale = size; }
		void SetCenter(Vector2 size) { mOffsetPosition = size; }
		
		UINT GetColliderID() { return mColliderID; }
		eColliderType GetType() { return mType; }

	private:
		static UINT mColliderNumber;
		UINT mColliderID;
		eColliderType mType;
		Transform* mTransform;

		Vector3 mColliderPosition;
		Vector2 mOffsetScale;
		Vector2 mOffsetPosition;
	};
}