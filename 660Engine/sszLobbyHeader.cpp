#include "sszLobbyHeader.h"
#include "CommonObjHeader.h"

#include "sszHeaderSlot.h"
#include "sszTGM.h"


namespace ssz
{
	LobbyHeader::LobbyHeader(const std::wstring& key)
		: UIObject(key)
		, mDateSlot(nullptr)
		, mGoldSlot(nullptr)
	{
		
	}

	LobbyHeader::~LobbyHeader()
	{
	}

	void LobbyHeader::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_HeaderMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"UIheaderBarTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header\\header_bg.png");

			// SlotIcon
			Resources::Load<Texture>(L"header_calendar_iconTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header\\header_calendar_icon.png");
			Resources::Load<Texture>(L"header_gold_iconTex", L"..\\Resources\\useResource\\Mainlobby\\UI\\header\\header_gold_icon.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"UIheaderBarTex", eRenderingMode::Transparent);
			ssz::object::LoadMaterial(L"CalendarIconMt", L"SpriteShader", L"header_calendar_iconTex", eRenderingMode::Transparent);
			ssz::object::LoadMaterial(L"GoldIconMt", L"SpriteShader", L"header_gold_iconTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Setting
		{
			// Set MeshRenderer
			AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

			// Set Panel
			AddComponent<PanelUI>();

			// Set default Size
			Transform* tr = GetComponent<Transform>();
			tr->SetScale(Vector3(1920, 111.f, 1.f));
		}
#pragma endregion
#pragma region SlotUI Load
		{
			mDateSlot = ssz::object::InstantiateUI<HeaderSlot>(Vector3(416.f, 0.f, 1.002f), this, L"DateSlot");
			mDateSlot->AddComponent<PanelUI>();
			
			mGoldSlot = ssz::object::InstantiateUI<HeaderSlot>(Vector3(775.f, 0.f, 1.002f), this, L"GlodSlot");
			mGoldSlot->AddComponent<PanelUI>();

			UIObject* CalendarIcon = ssz::object::InstantiateUI<UIObject>(Vector3(-133.f, 0.f, 1.001f), Vector3(36.f, 36.f, 1.f), mDateSlot, L"CalendarIcon");
			CalendarIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CalendarIconMt");
			CalendarIcon->GetComponent<Transform>()->SetTransType(ssz::Transform::eTransType::PosAdd);

			UIObject* GoldIcon = ssz::object::InstantiateUI<UIObject>(Vector3(-133.f, 0.f, 1.001f), Vector3(36.f, 36.f, 1.f), mGoldSlot, L"GoldIcon");
			GoldIcon->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"GoldIconMt");
			GoldIcon->GetComponent<Transform>()->SetTransType(ssz::Transform::eTransType::PosAdd);
		}
#pragma endregion
	}

	void LobbyHeader::LateUpdate()
	{
		UIObject::LateUpdate();

		wstring playerGold = std::to_wstring(TGM::GetPlayerGold());
		wstring Date =
			std::to_wstring(TGM::GetYear()) + L"년 " +
			std::to_wstring(TGM::GetMonth()) + L"월 " +
			std::to_wstring(TGM::GetWeek()) + L"주차";

		mDateSlot->GetComponent<Text>()->SetString(Date);
		mGoldSlot->GetComponent<Text>()->SetString(playerGold);
	}
}