#include "sszBanPickScene.h"
#include "CommonHeader.h"

#include "sszBattleHeader.h"
#include "sszBanLine.h"
#include "sszPlayerCardSlot.h"
#include "sszBanPickStat.h"

namespace ssz
{
	using namespace object;

	BanPickScene::BanPickScene()
	{
	}
	BanPickScene::~BanPickScene()
	{
	}
	void BanPickScene::Initialize()
	{
#pragma region Make Material for this Scene
		{
			// Texture Loading
			Resources::Load<Texture>(L"BanpickBgTex", L"..\\Resources\\useResource\\BanPick\\banpick_ui_bg.png");

			// Make Material
			LoadMaterial(L"BanpickBgMt", L"SpriteShader", L"BanpickBgTex", eRenderingMode::Transparent);
		}
#pragma endregion
#pragma region Create Object for this Scene
#pragma region GameObject
		// GameObject
		{
			// BanpickBg
			GameObject* BanpickBg = Instantiate<GameObject>(Vector3(0.0f, 0.0f, 1.1f), Vector3(1920.f, 1080.f, 1.f), eLayerType::BackGround);
			BanpickBg->SetName(L"BanpickBg");
			BanpickBg->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BanpickBgMt");
		}
#pragma endregion
#pragma region UI
		{
			// Battle Header
			BattleHeader* BattleHeaderBg = InstantiateUI<BattleHeader>(Vector3(0.0f, 478.5f, 1.04f), eLayerType::UI, L"BattleHeaderBg");

			// BanLine
			BanLine* BanLineUI = InstantiateUI<BanLine>(Vector3(0.f, 353.f, 1.03f), eLayerType::UI, L"BanLine");

			// PlayerCard
			InstantiateUI<PlayerCardSlot>(Vector3(843.f, 308.f, 1.02f), eLayerType::UI, L"RedPlayerCard_1")->SetRed();
			InstantiateUI<PlayerCardSlot>(Vector3(843.f, 69.f, 1.02f), eLayerType::UI, L"RedPlayerCard_2")->SetRed();
			InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 308.f, 1.02f), eLayerType::UI, L"BluePlayerCard_1")->SetBlue();
			InstantiateUI<PlayerCardSlot>(Vector3(-843.f, 69.f, 1.02f), eLayerType::UI, L"BluePlayerCard_2")->SetBlue();

			// StatSlot
			InstantiateUI<BanPickStat>(Vector3(-375.f, -116.f, 1.02f), eLayerType::UI, L"ATKStatSlot")->SetSlot(eStatType::ATK);
			InstantiateUI<BanPickStat>(Vector3(-215.f, -116.f, 1.02f), eLayerType::UI, L"DEFStatSlot")->SetSlot(eStatType::DEF);
			InstantiateUI<BanPickStat>(Vector3(-375.f, -185, 1.02f), eLayerType::UI, L"APDStatSlot")->SetSlot(eStatType::APD);
			InstantiateUI<BanPickStat>(Vector3(-215.f, -185, 1.02f), eLayerType::UI, L"HPStatSlot")->SetSlot(eStatType::HP);
			InstantiateUI<BanPickStat>(Vector3(-375.f, -254.f, 1.02f), eLayerType::UI, L"RNGStatSlot")->SetSlot(eStatType::RNG);
			InstantiateUI<BanPickStat>(Vector3(-215.f, -254.f, 1.02f), eLayerType::UI, L"SPDStatSlot")->SetSlot(eStatType::SPD);
		
			// BanpickClassTap
			// Ŭ�������� Btn �������� �θ�ü���� ���¸� �޾� ���õ� ��ư�� ������ ��ư�� ũ��� ��ġ�� �ٲ�� �Ѵ�.

			// ������Ʈ ��ġ�� ��ũ��Ʈ
		}
#pragma endregion
		
#pragma endregion
	}
	void BanPickScene::Update()
	{
		Scene::Update();

		if (Input::GetKeyDown(eKeyCode::ENTER))
		{
			SceneManager::LoadScene(L"IGStadiumScene");
		}
	}
	void BanPickScene::LateUpdate()
	{
		Scene::LateUpdate();
	}
	void BanPickScene::Render()
	{
		Scene::Render();
	}
	void BanPickScene::OnEnter()
	{
		Cursor::RegistCursor(this);
		MainCamera::RegistCamera(this);

		CollisionManager::SetLayer(eLayerType::UI, eLayerType::Cursor, true);
	}
	void BanPickScene::OnExit()
	{
		CollisionManager::Clear();

		Erase(eLayerType::Cursor);
		Erase(eLayerType::Camera);
	}
}