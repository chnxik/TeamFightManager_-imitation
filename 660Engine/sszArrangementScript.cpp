#include "sszArrangementScript.h"

#include "sszMath.h"

#include "sszApplication.h"

#include "sszGameObject.h"
#include "sszUIObject.h"

#include "sszInput.h"
#include "sszTime.h"

// Component
#include "sszTransform.h"
#include "sszCamera.h"

extern ssz::Application application;

namespace ssz
{
	ArrangementScript::ArrangementScript()
		: ArrangePos{}
		, ArrangeScale{}
		, mPrevMousePos{}
		, fradius(1.f)
		, fradiusx(1.f)
		, fradiusy(1.f)
		, OwnerUI(nullptr)
	{
	}

	ArrangementScript::~ArrangementScript()
	{
	}

	void ArrangementScript::Initialize()
	{
		// Owner 의 Transform에 접근해 초기 Pos와 Scale을 가져온다.
		Transform* OwnerTf = GetOwner()->GetComponent<Transform>();
		ArrangePos = OwnerTf->GetPosition();
		ArrangeScale = OwnerTf->GetScale();
		OwnerUI = dynamic_cast<UIObject*>(GetOwner());
	}
	
	void ArrangementScript::Update()
	{
		// Position
		if (Input::GetKey(eKeyCode::A))
		{
			if (Input::GetKey(eKeyCode::UP))	{ ArrangePos.y += 0.1f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::DOWN))	{ ArrangePos.y -= 0.1f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::LEFT))	{ ArrangePos.x -= 0.1f * (float)Time::DeltaTime(); }
			if (Input::GetKey(eKeyCode::RIGHT))	{ ArrangePos.x += 0.1f * (float)Time::DeltaTime(); }
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

		if (OwnerUI !=nullptr && OwnerUI->IsLbtnDown())
		{
			Vector3 CurPos = Input::GetMousePos4DX();

			Vector2 amount = mPrevMousePos - Vector2(CurPos.x,CurPos.y);

			ArrangePos.x -= amount.x;
			ArrangePos.y -= amount.y;

			mPrevMousePos = Vector2(CurPos.x,CurPos.y);
		}
		else
		{
			Vector3 CurPos = Input::GetMousePos4DX();
			mPrevMousePos = Vector2(CurPos.x, CurPos.y);
		}

		Vector3 FinalPos = ArrangePos;
		Vector3 FinalScale = {};
		FinalScale.x = ArrangeScale.x * fradius * fradiusx;
		FinalScale.y = ArrangeScale.y * fradius * fradiusy;
		FinalScale.z = 1.f;

		Transform* OwnerTf = GetOwner()->GetComponent<Transform>();
		OwnerTf->SetPosition(ArrangePos);
		OwnerTf->SetScale(FinalScale);

		if (Input::GetKeyDown(eKeyCode::RBUTTON))
		{
			int Fin = 0;
		}
	}

	void ArrangementScript::OnCollisionEnter(Collider2D* other)
	{
	}

	void ArrangementScript::OnCollisionStay(Collider2D* other)
	{
	}

	void ArrangementScript::OnCollisionExit(Collider2D* other)
	{
	}
}
