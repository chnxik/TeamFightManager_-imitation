#include "sszCollider2D.h"
#include "sszGameObject.h"

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
	}

	void Collider2D::Render()
	{
	}
}