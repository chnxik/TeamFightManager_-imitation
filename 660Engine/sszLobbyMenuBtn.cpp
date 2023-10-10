#include "sszLobbyMenuBtn.h"
#include "CommonHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	LobbyMenuBtn::LobbyMenuBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
		, mBtnIcon(nullptr)
		, useGray(false)
		, useAlpha(false)
		, grayRatio(0.5f)
		, AlphaRatio(1.f)
	{
		
	}

	LobbyMenuBtn::~LobbyMenuBtn()
	{
	}
	void LobbyMenuBtn::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_BtnMt");

#pragma region Meterial Load
		{

			Resources::Load<Texture>(L"MainMenuBtnIdleTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\menu\\main_menu_button_0.png");
			Resources::Load<Texture>(L"MainMenuBtnOnTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\menu\\main_menu_button_1.png");
			Resources::Load<Texture>(L"MainMenuBtnDownTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\btn\\menu\\main_menu_button_2.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"MainMenuBtnIdleTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);
			AddComponent<PanelUI>();

			// Set ButtonUI
			mBtnComp = AddComponent<ButtonUI>();
			mBtnComp->Initialize();
			mBtnComp->SetIdleTex(L"MainMenuBtnIdleTex");
			mBtnComp->SetOnTex(L"MainMenuBtnOnTex");
			mBtnComp->SetDownTex(L"MainMenuBtnDownTex");
			mBtnComp->SetBtnType(ssz::ButtonUI::eBtnType::Togle);

			// Set default Size
			GetComponent<Transform>()->SetScale(Vector3(230, 62.f, 1.f));
		}
#pragma endregion
	}

	void LobbyMenuBtn::Render()
	{
		// bind
		renderer::ColorFXCB data = {};
		
		data.useGray = useGray;
		data.useAlpha = useAlpha;
		data.GrayRatio = grayRatio;
		data.AlphaRatio = AlphaRatio;
		
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::ColorFX];
		cb->SetData(&data);
		
		cb->Bind(eShaderStage::PS);

		UIObject::Render();
	}

	void LobbyMenuBtn::InitBtnIcon(std::wstring Texkey, std::wstring MenuName)
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 Pos = tr->GetPosition();
		Vector3 Scale = tr->GetScale();
		std::wstring IconObjkey = GetName() + L"Icon";
		mBtnIcon = ssz::object::InstantiateUI<UIObject>(Vector3(-Scale.x/2.f + 30.f, 0.f, Pos.z), Vector3(30.f, 30.f, 1.f), this, IconObjkey);
		IconObjkey += L"_Mt";

		LoadMaterial(IconObjkey, L"SpriteShader", Texkey, eRenderingMode::Transparent);
		mBtnIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", IconObjkey);
		
		Transform* BtnIconTr = mBtnIcon->GetComponent<Transform>();
		BtnIconTr->SetTransType(ssz::Transform::eTransType::PosAdd);
		Vector3 IconPos = BtnIconTr->GetPosition();
		Vector3 IconScale = BtnIconTr->GetScale();

		Text* mMenuName = AddComponent<Text>();
		mMenuName->TextInit(L"Galmuri14", Vector3(IconPos.x + IconScale.x / 2.f + 5.f, 0.f, 0.f), 20.f, FONT_RGBA(255, 255, 255, 255), FW1_LEFT | FW1_VCENTER);
		mMenuName->SetString(MenuName);
	}
}
