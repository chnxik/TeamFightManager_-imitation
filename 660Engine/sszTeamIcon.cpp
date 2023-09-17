#include "sszTeamIcon.h"
#include "CommonObjHeader.h"

namespace ssz
{
	TeamIcon::TeamIcon(const std::wstring& key)
		: UIObject(key)
		, mBackGround(nullptr)
	{
	}

	TeamIcon::~TeamIcon()
	{
	}
	
	void TeamIcon::Initialize()
	{

		ssz::object::LoadMaterial(L"PlayerTeamLogoMt", L"SpriteShader", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"PlayerTeamLogoMt");

		GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);

		// Bg
		wstring objname = L"IconBG";

		Transform* tr = GetComponent<Transform>();
		Vector3 Pos = tr->GetPosition();
		Pos.z += 0.0001f;

		mBackGround = InstantiateUI<UIObject>(Pos, Vector3(100.f, 100.f, 1.f), GetParentUI(), objname);
		mBackGround->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);

		Resources::Load<Texture>(L"LogoBg", L"..\\Resources\\useResource\\UI\\slot_bg_0.png");
		ssz::object::LoadMaterial(L"LogoBgMt", L"SpriteShader", L"LogoBg", eRenderingMode::Transparent);
		mBackGround->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"LogoBgMt");
	}
	
	void TeamIcon::ChangeLogo(std::wstring Texkey)
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Texkey);
	}
}