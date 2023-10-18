#include "sszBattleHeader.h"
#include "CommonHeader.h"

#include "sszTGM.h"
#include "sszTeam.h"
#include "sszChamp.h"
#include "sszLeague.h"

#include "sszArrangementScript.h"

#include "sszTeamIconSlot.h"

namespace ssz
{
	BattleHeader::BattleHeader(const std::wstring& key)
		: UIObject(key)
		, mHeaderTextType(eHeaderTextType::GameTime)
		, mLeagueManager(nullptr)
		, mHeaderText(nullptr)
		, BlueTeam(nullptr)
		, RedTeam(nullptr)
		, BlueTeamName(nullptr)
		, RedTeamName(nullptr)
		, BlueTemaScore(nullptr)
		, RedTeamScore(nullptr)
		, BlueTKScoreValue(nullptr)
		, RedTKScoreValue(nullptr)
		, BlueRoundIcon(nullptr)
		, RedRoundIcon(nullptr)
	{
	}

	BattleHeader::~BattleHeader()
	{
	}

	void BattleHeader::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_HeaderMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"BattleHeaderTex", L"..\\Resources\\useResource\\Banpick\\header_bg.png");
			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"BattleHeaderTex", eRenderingMode::Transparent);
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
			tr->SetScale(Vector3(1920, 123.f, 1.f));

			mLeagueManager = TGM::GetLeagueManage();

			// Time
			mHeaderText = AddComponent<Text>();
			mHeaderText->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -30.f, 0.f), 25.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			mHeaderText->SetString(L"NONE");
		}
#pragma endregion
#pragma region SlotUI Load
		{
			BlueTeam = ssz::object::InstantiateUI<TeamIconSlot>(Vector3(-900.f, 8.f, 1.039f), Vector3(95.f, 95.f, 1.f), this, L"BlueTeamIconSlot");
			RedTeam = ssz::object::InstantiateUI<TeamIconSlot>(Vector3(900.f, 8.f, 1.039f), Vector3(95.f, 95.f, 1.f), this, L"RedTeamIconSlot");

			BlueTeamName = BlueTeam->AddComponent<Text>();
			RedTeamName = RedTeam->AddComponent<Text>();
			
			BlueTeamName->TextInit(Text::eFonts::Galmuri14, Vector3(350.f, 0.f, 0.f), 60.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			RedTeamName->TextInit(Text::eFonts::Galmuri14, Vector3(-350.f, 0.f, 0.f), 60.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);

			BlueTemaScore = BlueTeam->AddComponent<Text>();
			RedTeamScore = RedTeam->AddComponent<Text>();

			BlueTemaScore->TextInit(Text::eFonts::Galmuri14, Vector3(760.f, 10.f, 0.f), 55.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			BlueTemaScore->SetString(std::to_wstring(0));
			RedTeamScore->TextInit(Text::eFonts::Galmuri14, Vector3(-760.f, 10.f, 0.f), 55.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
			RedTeamScore->SetString(std::to_wstring(0));
			
			BlueRoundIcon = ssz::object::InstantiateUI<TeamIconSlot>(Vector3(-185.f, -30.f, 0.f), Vector3(30.f, 30.f, 1.f), this, L"BlueTeamRoundIcon");
			RedRoundIcon = ssz::object::InstantiateUI<TeamIconSlot>(Vector3(185.f, -30.f, 0.f), Vector3(30.f, 30.f, 1.f), this, L"RedTeamRoundIcon");
		}
#pragma endregion
	}
	void BattleHeader::Update()
	{
		if (mHeaderTextType == eHeaderTextType::GameTime)
		{
			float gametime = TGM::GetGameTime() - (float)Time::DeltaTime();
			std::wstring gt = L": ";
			gt += std::to_wstring((UINT)gametime);

			GetComponent<Text>()->SetString(gt);

			BlueTemaScore->SetString(std::to_wstring(*BlueTKScoreValue));
			RedTeamScore->SetString(std::to_wstring(*RedTKScoreValue));
		}

		GameObject::Update();
	}
	
	void BattleHeader::RegistTeam()
	{
		Team* PlayerTeam = TGM::GetPlayerTeam();
		Team* EnemyTeam = TGM::GetLeagueManage()->GetEnemyTeam();

		BlueTeam->ChangeIcon(PlayerTeam->GetTeamIconTexKey());
		RedTeam->ChangeIcon(EnemyTeam->GetTeamIconTexKey());

		BlueTeamName->SetString(PlayerTeam->GetTeamName());
		RedTeamName->SetString(EnemyTeam->GetTeamName());

		BlueTKScoreValue = PlayerTeam->GetTKScoreAddress();
		RedTKScoreValue = EnemyTeam->GetTKScoreAddress();
	}

	void BattleHeader::SetTimeType()
	{
		mHeaderTextType = eHeaderTextType::GameTime;
		mHeaderText->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -43.f, 0.f), 25.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
	}

	void BattleHeader::SetTitleType()
	{
		mHeaderTextType = eHeaderTextType::RoundTitle;
		
		std::wstring RoundTitle = L"어소트락 리그 " + std::to_wstring((UINT)mLeagueManager->GetCurRound() + 1) + L" 라운드";
		
		mHeaderText->TextInit(Text::eFonts::Galmuri14, Vector3(0.f, -43.f, 0.f), 25.f, FONT_RGBA(255, 255, 255, 255), FW1_CENTER | FW1_VCENTER);
		mHeaderText->SetString(RoundTitle);
	}
}