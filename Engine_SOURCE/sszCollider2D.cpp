#include "sszCollider2D.h"
#include "sszGameObject.h"
#include "sszRenderer.h"

namespace ssz
{
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mType(eColliderType::End)
		, mTransform(nullptr)
		, mSize(Vector2::One)
		, mCenter(Vector2::Zero)
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
		Vector3 FinalScale = mTransform->GetScale();
		FinalScale.x *= mSize.x;
		FinalScale.y *= mSize.y;

		Vector3 pos = mTransform->GetPosition();
		pos.x += mCenter.x;
		pos.y += mCenter.y;

		
		graphics::DebugMesh mesh = {};
		mesh.position;
		mesh.scale;
		mesh.rotation;
		mesh.type = mType;

		renderer::PushDebugMeshAttribute(mesh);
	}

	void Collider2D::Render()
	{
	}
}