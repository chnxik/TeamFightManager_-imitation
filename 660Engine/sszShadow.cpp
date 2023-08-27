#include "sszShadow.h"
#include "CommonObjHeader.h"

namespace ssz
{
	Shadow::Shadow()
	{
	}
	
	Shadow::~Shadow()
	{
	}
	
	void Shadow::Initialize()
	{
		Resources::Load<Texture>(L"ShadowTex", L"..\\Resources\\useResource\\ChampSprite\\common\\player_shadow.png");
		LoadMaterial(L"ShadowMt", L"SpriteShader", L"ShadowTex", eRenderingMode::Transparent);

		SetName(L"Shadow");
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"ShadowMt");
	}
	
	void Shadow::RegistChamp(Champ* owner)
	{
		Transform* Shadowtr = GetComponent<Transform>();
		Transform* Ownertr = owner->GetComponent<Transform>();

		Shadowtr->SetParent(Ownertr);
		Shadowtr->SetTransType(Transform::eTransType::PosAdd);
		Shadowtr->SetPosition(Vector3(0.f, -23.f, 1.2f));
		Shadowtr->SetScale(Vector3(40.f, 23.f, 1.f));
	}
}