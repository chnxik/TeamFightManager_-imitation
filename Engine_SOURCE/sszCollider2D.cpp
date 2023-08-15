#include "sszCollider2D.h"
#include "sszGameObject.h"
#include "sszRenderer.h"

namespace ssz
{
	using namespace ssz::graphics;

	UINT Collider2D::mColliderNumber = 1;
	Collider2D::Collider2D()
		: Component(eComponentType::Collider2D)
		, mType(eColliderType::Rect)
		, mTransform(nullptr)
		, mOffsetScale(Vector3::One)
		, mOffsetPosition(Vector3::Zero)
		, mColliderID(mColliderNumber++)
		, mOverlapCnt(0)
		, mFinalScale(Vector3::One)
		, mFinalPos(Vector3::Zero)
		, mFinalRotation(Vector3::Zero)
		, Axis{}
		, mColState(eColState::Active)
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
		assert(!(mOverlapCnt < 0)); // ��ø�� ������ ���
	}

	void Collider2D::LateUpdate()
	{
		mFinalScale = mTransform->GetWorldScale();
		mFinalScale += mOffsetScale;

		mFinalPos = mTransform->GetWorldPosition();
		mFinalPos += mOffsetPosition;

		mFinalRotation = mTransform->GetWorldRotation();

		Axis[eAxis::Right] = mTransform->Right();
		Axis[eAxis::Up] = mTransform->Up();

		graphics::DebugMesh mesh = {};
		mesh.position = mFinalPos;
		mesh.scale = mFinalScale;
		mesh.rotation = mFinalRotation;
		mesh.type = mType;
		mesh.OverlapCnt = mOverlapCnt;

		renderer::PushDebugMeshAttribute(mesh);
	}

	void Collider2D::Render()
	{
	}

	void Collider2D::Binds()
	{
	}

	void Collider2D::OnCollisionEnter(Collider2D* other)
	{
		++mOverlapCnt;

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
		--mOverlapCnt;

		const std::vector<Script*>& scripts
			= GetOwner()->GetScripts();

		for (Script* script : scripts)
		{
			script->OnCollisionExit(other);
		}
	}
	float Collider2D::GetLength4OBB(Vector3 MainAxis)
	{
		float res = 0.f;

		Vector3 TargetAxisRight = Axis[eAxis::Right];
		Vector3 TargetAxisUp = Axis[eAxis::Up];

		// Right��(�������� + �� ����)�� Up���� ���� �����࿡ ������Ű�� �� ���� ���Ѵ�.
		res = abs(TargetAxisRight.Dot(MainAxis) * (mFinalScale.x) / 2.f) +
			abs(TargetAxisUp.Dot(MainAxis) * (mFinalScale.y) / 2.f);

		return res;
	}
}