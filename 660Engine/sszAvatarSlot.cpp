#include "sszAvatarSlot.h"
#include "CommonHeader.h"

namespace ssz
{
	AvatarSlot::AvatarSlot(const std::wstring& key)
		: UIObject(key)
		, mAvatarBody(nullptr)
		, mAvatarHair(nullptr)
	{
	}

	AvatarSlot::~AvatarSlot()
	{
	}
	
	void AvatarSlot::Initialize()
	{
		Resources::Load<Texture>(L"IconSlotBg", L"..\\Resources\\useResource\\UI\\slot_bg_0.png");
		ssz::object::LoadMaterial(L"IconSlotMt", L"SpriteShader", L"IconSlotBg", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IconSlotMt");

		GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);

		Transform* tr = GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		pos.z -= 0.0001f;

		// 바디
		mAvatarBody = InstantiateUI<UIObject>(pos, Vector3(180.f, 180.f, 1.f), GetParentUI(), GetName() + L"BodyObj");
		mAvatarBody->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);

		Resources::Load<Texture>(L"SelAvatarBodyTex", L"..\\Resources\\useResource\\Avatar\\Coach\\coach_character_0.png");
		ssz::object::LoadMaterial(L"SelAvatarBodyMt", L"SpriteShader", L"SelAvatarBodyTex", eRenderingMode::Transparent);
		mAvatarBody->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"SelAvatarBodyMt");

		// 헤어
		pos.y += 22.f;
		pos.z -= 0.0001f;
		mAvatarHair = InstantiateUI<UIObject>(pos, Vector3(50.f, 50.f, 1.f), GetParentUI(), GetName() + L"HairObj");
		mAvatarHair->GetComponent<Transform>()->SetTransType(Transform::eTransType::PosAdd);

		ssz::object::LoadMaterial(L"SelAvatarHairMt", L"SpriteShader", eRenderingMode::Transparent);
		mAvatarHair->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"SelAvatarHairMt");
	}
	
	void AvatarSlot::ChangeHair(std::wstring Texkey)
	{
		mAvatarHair->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(Texkey);
		Vector2 TexSize = Resources::Find<Texture>(Texkey)->GetTextureSize();
		Vector3 TexScale(TexSize.x * 3.f, TexSize.y * 3.f, 1.f);

		mAvatarHair->GetComponent<Transform>()->SetScale(TexScale);
	}
}