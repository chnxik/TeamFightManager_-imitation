#pragma once
#include "sszProjScript.h"
#include "CommonObjHeader.h"

#include "sszBattleManager.h"
#include "sszProjectile.h"
#include "sszTGM.h"

namespace ssz
{
	ProjScript::ProjScript()
		: vSrcPos{}
		, vDestPos{}
		, vDir{}
		, mSrc(nullptr)
		, mDest(nullptr)
		, mDmg(0)
		, fLifeTime(0.f)
	{
	}

	ProjScript::~ProjScript()
	{
	}
	
	void ProjScript::Update()
	{
	}
	
	void ProjScript::LateUpdate()
	{
		Transform* Ownertr = GetOwner()->GetComponent<Transform>();
		
		Vector3 vPos = Ownertr->GetPosition();
		vPos.x += vDir.x * 500.f * (float)Time::DeltaTime();
		vPos.y += vDir.y * 500.f * (float)Time::DeltaTime();

		Ownertr->SetPosition(vPos);
		
		RECT stadiumSize = TGM::GetStadiumSize();
		
		if (vPos.x <= stadiumSize.left ||
			vPos.x >= stadiumSize.right ||
			vPos.y >= stadiumSize.top ||
			vPos.y <= stadiumSize.bottom)
		{
			Projectile* Owner = (Projectile*)GetOwner();

			Owner->SetPaused();
			Owner->bCanUse = true;
			SceneManager::GetActiveScene()->Erase(Owner->GetLayerType(), Owner);
		}
	}

	void ProjScript::SetProjInfo(Champ* Src, Champ* Dest, UINT Dmg)
	{
		mSrc = Src;
		mDest = Dest;

		Transform* Ownertr = GetOwner()->GetComponent<Transform>();

		vSrcPos = mSrc->GetComponent<Transform>()->GetPosition();
		vDestPos = mDest->GetComponent<Transform>()->GetPosition();

		vDir = vDestPos - vSrcPos;
		vDir.Normalize();

		float fradian = atan2(vDir.y, vDir.x);

		Vector3 test(0.f, 0.f, fradian);
		Ownertr->SetRotation(test);
		Ownertr->SetPosition(vSrcPos);
		
		mDmg = Dmg;
		fLifeTime = 0.f;
	}

	void ProjScript::OnCollisionStay(Collider2D* other)
	{
		Collider2D* DestCol = mDest->GetComponent<Collider2D>();
		if (other == DestCol)
		{
			BattleManager::ATTACK(mSrc, mDest, mDmg);
			Projectile* Owner = (Projectile*)GetOwner();

			Owner->SetPaused();
			Owner->bCanUse = true;
			SceneManager::GetActiveScene()->Erase(Owner->GetLayerType(), Owner);
		}
	}

}