#include "sszArrangementScript.h"

#include "sszGameObject.h"

#include "sszInput.h"
#include "sszTime.h"

// Component
#include "sszTransform.h"

namespace ssz
{
	ArrangementScript::ArrangementScript()
		: ArrangePos{}
		, ArrangeScale{}
		, fradius(1.f)
		, fradiusx(1.f)
		, fradiusy(1.f)
	{
	}

	ArrangementScript::~ArrangementScript()
	{
	}

	void ArrangementScript::Initialize()
	{
	}

	void ArrangementScript::SetDefault()
	{
		// Owner 의 Transform에 접근해 초기 Pos와 Scale을 가져온다.
		Transform* OwnerTf = GetOwner()->GetComponent<Transform>();
		ArrangePos = OwnerTf->GetLocalPosition();
		ArrangeScale = OwnerTf->GetLocalScale();
	}

	void ArrangementScript::Update()
	{
		// Position
		if (Input::GetKey(eKeyCode::A))
		{
			if (Input::GetKey(eKeyCode::UP))	{ ArrangePos.y += 10.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN))	{ ArrangePos.y -= 10.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::LEFT))	{ ArrangePos.x -= 10.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::RIGHT))	{ ArrangePos.x += 10.f * (float)Time::DeltaTime(); }
		}

		
		// Scale
		else if (Input::GetKey(eKeyCode::S))
		{
			if (Input::GetKey(eKeyCode::UP))	{ fradius += 1.f *		(float)Time::DeltaTime();}
			if (Input::GetKey(eKeyCode::DOWN))	{ fradius -= 1.f *		(float)Time::DeltaTime();}
			if (Input::GetKey(eKeyCode::LEFT))	{ fradius -= 0.01f *	(float)Time::DeltaTime();}
			if (Input::GetKey(eKeyCode::RIGHT))	{ fradius += 0.01f *	(float)Time::DeltaTime(); }
		}

		else if (ssz::Input::GetKey(eKeyCode::D))
		{
			if (Input::GetKey(eKeyCode::UP))	{ fradiusy += 1.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN))	{ fradiusy -= 1.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::LEFT))	{ fradiusx -= 1.f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::RIGHT)) { fradiusx += 1.f * (float)Time::DeltaTime(); }
		}

		

		Vector3 FinalPos = ArrangePos;
		Vector3 FinalScale = {};
		FinalScale.x = ArrangeScale.x * fradius * fradiusx;
		FinalScale.y = ArrangeScale.y * fradius * fradiusy;
		FinalScale.z = 1.f;

		Transform* OwnerTf = GetOwner()->GetComponent<Transform>();
		OwnerTf->SetLocalPosition(ArrangePos);
		OwnerTf->SetLocalScale(FinalScale);
	}
	
}
