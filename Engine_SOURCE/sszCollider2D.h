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

		void SetType(eColliderType type) { mType = type; }
		void SetSize(Vector2 size) { mOffsetScale = size; }
		void SetCenter(Vector2 size) { mOffsetPosition = size; }

	private:
		eColliderType mType;
		Transform* mTransform;

		Vector3 mColliderPosition;
		Vector2 mOffsetScale;
		Vector2 mOffsetPosition;
	};
}