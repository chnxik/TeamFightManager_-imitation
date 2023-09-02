#include "sszNumb.h"
#include "CommonObjHeader.h"

// atlas 350 * 96
// frame 35 * 48

// 0 ~ 9 : 31
// 1 : 18
// 4 : 35

namespace ssz
{
	Numb::Numb()
		: mMr(nullptr)
		, mRb(nullptr)
		, fLifeTime(0.f)
	{
	}

	Numb::~Numb()
	{
	}

	void Numb::Update()
	{
		fLifeTime += DT;

		if (0.37f < fLifeTime)
			SetState(eState::Dead);

		GameObject::Update();
	}
	
	void Numb::Initialize()
	{
		GetComponent<Transform>()->SetScale(Vector3(0.f, 20.f, 0.f));

		mRb = AddComponent<Rigidbody>();
		mMr = AddComponent<MeshRenderer>();

	}

	void Numb::PrintDamageBox(eDmgBoxType type, wstring numbstr)
	{
		mMr->SetMeshRenderer(L"RectMesh", numbstr);

		Transform* tr = GetComponent<Transform>();
		Vector3 vPos = tr->GetPosition();

		Vector3 vScale = tr->GetScale();
		vScale.x = vScale.y * (31.f/48.f);
		
		if (type == eDmgBoxType::DAMAGE)
			mRb->SetVelocity(Vector2(40.f, 200.f));

		else if (type == eDmgBoxType::HEAL)
		{
			mRb->SetFriction(0.f);
			mRb->SetGravityAccel(0.f);
			mRb->SetVelocity(Vector2(0.f, 20.f));
		}

		if(numbstr == L"dmg_1" || numbstr == L"heal_1")
			vScale.x = vScale.y * (18.f / 48.f);
		else if(numbstr == L"dmg_4" || numbstr == L"heal_4")
			vScale.x = vScale.y * (35.f / 48.f);

		tr->SetScale(vScale);
	}
}