#include "sszStatIcon.h"
#include "CommonObjHeader.h"

namespace ssz
{
	StatIcon::StatIcon(const std::wstring& key)
		: UIObject(key)
		, mStatIconTex {}
	{
		std::wstring MtKey(mUIKey + L"_IconMt");

#pragma region Meterial Load
		{
			// Icon
			mStatIconTex[eStatType::ATK] = Resources::Load<Texture>(L"ATKIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_0.png");
			mStatIconTex[eStatType::DEF] = Resources::Load<Texture>(L"DEFIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_1.png");
			mStatIconTex[eStatType::APD] = Resources::Load<Texture>(L"APDIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_2.png");
			mStatIconTex[eStatType::HP] = Resources::Load<Texture>(L"HPIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_3.png");
			mStatIconTex[eStatType::RNG] = Resources::Load<Texture>(L"RNGIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_4.png");
			mStatIconTex[eStatType::SPD] = Resources::Load<Texture>(L"SPDIconTex", L"..\\Resources\\useResource\\Banpick\\ingame_stat_icon_5.png");

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

	StatIcon::~StatIcon()
	{
	}
	void StatIcon::SetIcon(eStatType eType)
	{
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(mStatIconTex[eType]);
	}
}