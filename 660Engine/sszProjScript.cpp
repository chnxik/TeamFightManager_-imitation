#pragma once
#include "sszProjScript.h"
#include "CommonObjHeader.h"

#include "sszBattleManager.h"
#include "sszProjectile.h"

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
		vPos.x += vDir.x * 300.f * (float)Time::DeltaTime();
		vPos.y += vDir.y * 300.f * (float)Time::DeltaTime();

		Ownertr->SetPosition(vPos);
		
		fLifeTime += (float)Time::DeltaTime();
		if (2.f < fLifeTime)
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
		vDir.z = 0.f;
		vDir.Normalize();

		Ownertr->SetPosition(vSrcPos);
		Ownertr->SetRotation(vDir);
		
		mDmg = Dmg;
		fLifeTime = 0.f;
	}

	void ProjScript::OnCollisionEnter(Collider2D* other)
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