#include "sszTestScript.h"

#include "sszGameObject.h"

#include "sszInput.h"
#include "sszTime.h"

// Component
#include "sszTransform.h"

namespace ssz
{
	TestScript::TestScript()
		: OffsetPos{}
		, OffsetScale{}
		, OffsetRotation{}
		, fradius(1.f)
		, fradiusx(1.f)
		, fradiusy(1.f)
	{
	}

	TestScript::~TestScript()
	{
	}

	void TestScript::Initialize()
	{
	}

	void TestScript::SetDefault()
	{
		// Owner �� Transform�� ������ �ʱ� Pos�� Scale�� �����´�.
		Transform* OwnerTf = GetOwner()->GetComponent<Transform>();
		OffsetPos = OwnerTf->GetPosition();
		OffsetScale = OwnerTf->GetScale();
		OffsetRotation = OwnerTf->GetRotation();
	}

	void TestScript::Update()
	{
		// Position
		if (Input::GetKey(eKeyCode::Q))
		{
			if (Input::GetKey(eKeyCode::UP)) { OffsetPos.y += 100.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN)) { OffsetPos.y -= 100.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::LEFT)) { OffsetPos.x -= 100.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::RIGHT)) { OffsetPos.x += 100.f * (float)Time::DeltaTime(); }
		}


		// Scale
		if (Input::GetKey(eKeyCode::W))
		{
			if (Input::GetKey(eKeyCode::UP)) { fradius += 50.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN)) { fradius -= 50.f * (float)Time::DeltaTime(); }
		}

		// Rotation
		float RotZ = RtoD(OffsetRotation.z);
		if (ssz::Input::GetKey(eKeyCode::E))
		{
			if (Input::GetKey(eKeyCode::UP)) { RotZ += 10.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN)) { RotZ -= 10.f * (float)Time::DeltaTime(); }
		}
		OffsetRotation.z = DtoR(RotZ);

		Vector3 FinalPos = OffsetPos;
		Vector3 FinalScale = {};
		Vector3 FinalRotation = OffsetRotation;
		FinalScale.x = OffsetScale.x + fradius;
		FinalScale.y = OffsetScale.y + fradius;
		FinalScale.z = 1.f;

		Transform* OwnerTf = GetOwner()->GetComponent<Transform>();
		OwnerTf->SetPosition(FinalPos);
		OwnerTf->SetScale(FinalScale);
		OwnerTf->SetRotation(FinalRotation);
	}
}
