#include "sszProjectile.h"
#include "CommonHeader.h"

#include "sszChamp.h"
#include "sszProjScript.h"

namespace ssz
{
	Projectile::Projectile()
		: bCanUse(true)
	{
	}

	Projectile::~Projectile()
	{
	}

	void Projectile::Initialize()
	{
		AddComponent<Collider2D>();
		AddComponent<MeshRenderer>();

		AddComponent<Animator>();
		AddComponent<ProjScript>();
	}

	void Projectile::Shoot(Champ* Src, Champ* Dest, Vector3 ProjScale, const std::wstring& Materialkey, UINT Dmg)
	{
		GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", Materialkey);
		GetComponent<ProjScript>()->SetProjInfo(Src, Dest, Dmg);

		// Layer µî·Ï
		eLayerType Layertype = eLayerType::End;

		switch (Src->GetLayerType())
		{
		case ssz::enums::eLayerType::Player:
		{	Layertype = eLayerType::PlayerInteraction;	break;	}
		case ssz::enums::eLayerType::Enemy:
		{	Layertype = eLayerType::EnemyInteraction;	break;	}
		}

		GetComponent<Transform>()->SetScale(ProjScale);

		SetLayerType(Layertype);
		SceneManager::GetActiveScene()->AddGameObject(Layertype, this);

		SetActive();
		bCanUse = false;
	}
}