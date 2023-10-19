#pragma once
#include "sszProjScript.h"
#include "CommonHeader.h"

#include "sszBattleManager.h"
#include "sszTGM.h"

#include "sszChamp.h"
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
		if (0.5f < fLifeTime)
		{
			Projectile* Owner = (Projectile*)GetOwner();

			Owner->SetPaused();
			Owner->bCanUse = true;
			SceneManager::GetActiveScene()->Erase(Owner->GetLayerType(), Owner);
		}
		
		if (0.f < fLifeTime)
		{
			fLifeTime += (float)Time::DeltaTime();
			return;
		}

		Transform* Ownertr = GetOwner()->GetComponent<Transform>();
		
		float Speed = 800.f;

		Vector3 vPos = Ownertr->GetPosition();
		vPos.x += vDir.x * Speed * (float)Time::DeltaTime();
		vPos.y += vDir.y * Speed * (float)Time::DeltaTime();

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
			Transform* Ownertr = GetOwner()->GetComponent<Transform>();
			Ownertr->SetPosition(other->GetOwner()->GetComponent<Transform>()->GetPosition());

			if (0.f == fLifeTime)
			{
				BattleManager::ATTACK(mSrc, mDest, mDmg);
				fLifeTime += (float)Time::DeltaTime();
			}
		}
	}

}