#include "sszKBDIcon.h"
#include "CommonHeader.h"

namespace ssz
{
	KBDIcon::KBDIcon(const std::wstring& key)
		: UIObject(key)
	{
	}

	KBDIcon::~KBDIcon()
	{
	}

	void KBDIcon::Initialize()
	{
	}
	void KBDIcon::SetIcon(KEYICON key)
	{
		std::shared_ptr<Texture> IconTex = nullptr;
		std::wstring MtKey = {};

		switch (key)
		{
		case ssz::KBDIcon::A:
			IconTex = Resources::Load<Texture>(L"KBD_A_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_a.png");
			MtKey = L"KBD_A";
			break;
		case ssz::KBDIcon::C:
			IconTex = Resources::Load<Texture>(L"KBD_C_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_c.png");
			MtKey = L"KBD_C";
			break;
		case ssz::KBDIcon::D:
			IconTex = Resources::Load<Texture>(L"KBD_D_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_d.png");
			MtKey = L"KBD_D";
			break;
		case ssz::KBDIcon::E:
			IconTex = Resources::Load<Texture>(L"KBD_E_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_e.png");
			MtKey = L"KBD_E";
			break;
		case ssz::KBDIcon::F:
			IconTex = Resources::Load<Texture>(L"KBD_F_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_f.png");
			MtKey = L"KBD_F";
			break;
		case ssz::KBDIcon::Q:
			IconTex = Resources::Load<Texture>(L"KBD_Q_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_q.png");
			MtKey = L"KBD_Q";
			break;
		case ssz::KBDIcon::R:
			IconTex = Resources::Load<Texture>(L"KBD_R_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_r.png");
			MtKey = L"KBD_R";
			break;
		case ssz::KBDIcon::S:
			IconTex = Resources::Load<Texture>(L"KBD_S_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_s.png");
			MtKey = L"KBD_S";
			break;
		case ssz::KBDIcon::V:
			IconTex = Resources::Load<Texture>(L"KBD_V_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_v.png");
			MtKey = L"KBD_V";
			break;
		case ssz::KBDIcon::Z:
			IconTex = Resources::Load<Texture>(L"KBD_Z_IconTex", L"..\\Resources\\useResource\\UI\\keyboard_buttons_z.png");
			MtKey = L"KBD_Z";
			break;
		default:
			break;
		}

		 MtKey += L"_IconMt";

		ssz::object::LoadMaterial(MtKey, L"SpriteShader", eRenderingMode::Transparent);
		MeshRenderer* mr = AddComponent<MeshRenderer>();
		mr->SetMeshRenderer(L"RectMesh", MtKey);
		mr->GetMaterial()->SetTexture(IconTex);

		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(47.f, 47.f, 0.f));
		tr->SetPosition(Vector3(-65.f, 0.f, 0.f));
		tr->SetTransType(ssz::Transform::eTransType::PosAdd);
	}
}