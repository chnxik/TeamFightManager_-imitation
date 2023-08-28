#pragma once
#include "sszScript.h"

namespace ssz
{
    class ProjScript : public Script
    {
	public:
		ProjScript();
		virtual ~ProjScript();

		virtual void Update() override;
		virtual void LateUpdate() override;

		void SetProjInfo(Champ* Src, Champ* Dest, UINT Dmg);

		virtual void OnCollisionEnter(Collider2D* other);

	private:
		Vector3 vSrcPos;
		Vector3 vDestPos;
		Vector3 vDir;
		Champ* mSrc;
		Champ* mDest;
		UINT mDmg;

		float fLifeTime;
    };
}