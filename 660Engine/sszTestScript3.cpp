#include "sszTestScript3.h"

#include "sszGameObject.h"

#include "sszInput.h"
#include "sszTime.h"

// Component
#include "sszTransform.h"

namespace ssz
{
	TestScript3::TestScript3()
		: OffsetPos{}
		, OffsetScale{}
		, OffsetRotation{}
		, fradius(1.f)
		, fradiusx(1.f)
		, fradiusy(1.f)
	{
	}

	TestScript3::~TestScript3()
	{
	}

	void TestScript3::Initialize()
	{
	}

	void TestScript3::SetDefault()
	{
		// Owner 의 Transform에 접근해 초기 Pos와 Scale을 가져온다.
		Transform* OwnerTf = GetOwner()->GetComponent<Transform>();
		OffsetPos = OwnerTf->GetPosition();
		OffsetScale = OwnerTf->GetScale();
		OffsetRotation = OwnerTf->GetRotation();
	}

	void TestScript3::Update()
	{
		// Position
		if (Input::GetKey(eKeyCode::Z))
		{
			if (Input::GetKey(eKeyCode::UP)) { OffsetPos.y += 100.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN)) { OffsetPos.y -= 100.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::LEFT)) { OffsetPos.x -= 100.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::RIGHT)) { OffsetPos.x += 100.f * (float)Time::DeltaTime(); }
		}


		// Scale
		if (Input::GetKey(eKeyCode::X))
		{
			if (Input::GetKey(eKeyCode::UP)) { fradius += 50.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN)) { fradius -= 50.f * (float)Time::DeltaTime(); }
		}

		// Rotation
		float RotZ = RtoD(OffsetRotation.z);
		if (ssz::Input::GetKey(eKeyCode::C))
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
