#include "sszLobbyMenuBtn.h"
#include "CommonObjHeader.h"

#include "sszButtonUI.h"

namespace ssz
{
	LobbyMenuBtn::LobbyMenuBtn(const std::wstring& Key)
		: UIObject(Key)
		, mBtnComp(nullptr)
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
}
