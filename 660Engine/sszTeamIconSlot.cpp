#include "sszTeamIconSlot.h"
#include "CommonObjHeader.h"

namespace ssz
{
	TeamIconSlot::TeamIconSlot(const std::wstring& key)
		: UIObject(key)
		, mTeamIcon(nullptr)
	{
	}

	TeamIconSlot::~TeamIconSlot()
	{
	}
	
	void TeamIconSlot::Initialize()
	{
		Resources::Load<Texture>(L"IconSlotBg", L"..\\Resources\\useResource\\UI\\slot_bg_0.png");
		ssz::object::LoadMaterial(L"IconSlotMt", L"SpriteShader", L"IconSlotBg", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IconSlotMt");
		
		GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);
		
		wstring IconObjkey = GetName() + L"TexObj";
		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.z -= 0.0001f;

		Vector3 Scale = tr->GetScale();
		mTeamIcon = InstantiateUI<UIObject>(pos, Scale, GetParentUI(), IconObjkey);
		mTeamIcon->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);

		ssz::object::LoadMaterial(L"TeamIconMt", L"SpriteShader", eRenderingMode::Transparent);
		mTeamIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"TeamIconMt");
	}
	
	void TeamIconSlot::ChangeIcon(std::wstring Texkey)
	{
		mTeamIcon->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Texkey);
		mTeamIconTexKey = Texkey;
	}
}