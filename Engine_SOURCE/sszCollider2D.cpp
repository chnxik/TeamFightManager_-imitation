#include "sszCollider2D.h"
#include "sszGameObject.h"
#include "sszRenderer.h"

namespace ssz
{
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mType(eColliderType::Rect)
		, mTransform(nullptr)
		, mOffsetScale(Vector2::One)
		, mOffsetPosition(Vector2::Zero)
	{
	}

	Collider2D::~Collider2D()
	{
	}

	void Collider2D::Initialize()
	{
		mTransform = GetOwner()->GetComponent<Transform>();
	}

	void Collider2D::Update()
	{
	}

	void Collider2D::LateUpdate()
	{
		Vector3 scale = mTransform->GetWorldScale();
		scale.x *= mOffsetScale.x;
		scale.y *= mOffsetScale.y;

		Vector3 pos = mTransform->GetWorldPosition();
		pos.x += mOffsetPosition.x;
		pos.y += mOffsetPosition.y;

		mColliderPosition = pos;

		graphics::DebugMesh mesh = {};
		mesh.position = pos;
		mesh.scale = scale;
		mesh.rotation = mTransform->GetWorldRotation();
		mesh.type = eColliderType::Rect;

		renderer::PushDebugMeshAttribute(mesh);
	}

	void Collider2D::Render()
	{
	}
}