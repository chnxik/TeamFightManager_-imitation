#include "sszStatIcon.h"
#include "CommonHeader.h"

namespace ssz
{
	StatIcon::StatIcon(const std::wstring& key)
		: UIObject(key)
		, mStatIconTex {}
	{
		
	}

	StatIcon::~StatIcon()
	{
	}
	void StatIcon::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_IconMt");

#pragma region Meterial Load
		{
			// Icon
			mStatIconTex[(UINT)eStatType::ATK] = Resources::Load<Texture>(L"ATKIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_0.png");
			mStatIconTex[(UINT)eStatType::DEF] = Resources::Load<Texture>(L"DEFIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_1.png");
			mStatIconTex[(UINT)eStatType::APD] = Resources::Load<Texture>(L"APDIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_2.png");
			mStatIconTex[(UINT)eStatType::HP] = Resources::Load<Texture>(L"HPIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_3.png");
			mStatIconTex[(UINT)eStatType::RNG] = Resources::Load<Texture>(L"RNGIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_4.png");
			mStatIconTex[(UINT)eStatType::SPD] = Resources::Load<Texture>(L"SPDIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_5.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"ATKIconTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(26.f, 26.f, 1.f));
			tr->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
	}
	void StatIcon::SetIcon(eStatType eType)
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(mStatIconTex[(UINT)eType]);
	}
}