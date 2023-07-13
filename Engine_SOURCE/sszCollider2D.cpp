#include "sszCollider2D.h"
#include "sszGameObject.h"
#include "sszRenderer.h"

namespace ssz
{
	UINT Collider2D::mColliderNumber = 1;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mType(eColliderType::Rect)
		, mTransform(nullptr)
		, mOffsetScale(Vector2::One)
		, mOffsetPosition(Vector2::Zero)
		, mColliderID(mColliderNumber++)
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
		mesh.radius = (scale.x + scale.y) / 4.f;
		mesh.rotation = mTransform->GetWorldRotation();
		mesh.type = mType;

		renderer::PushDebugMeshAttribute(mesh);
	}

	void Collider2D::Render()
	{
	}

	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetScripts();

		for (Script* script : scripts)
		{
			script->OnCollisionEnter(other);
		}
	}
	void Collider2D::OnCollisionStay(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetScripts();

		for (Script* script : scripts)
		{
			script->OnCollisionStay(other);
		}
	}
	void Collider2D::OnCollisionExit(Collider2D* other)
	{
		const std::vector<Script*>& scripts
			= GetOwner()->GetScripts();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}
}