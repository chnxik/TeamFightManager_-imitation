#include "sszBanLine.h"
#include "CommonHeader.h"

namespace ssz
{
	BanLine::BanLine(const std::wstring& key)
		: UIObject(key)
		, mCurTeamColor(eTeamColor::Blue)
		, mArrowMark(nullptr)
		, mPhaseCenterStr(nullptr)
		, mPhaseSideStr(nullptr)
	{
	}

	BanLine::~BanLine()
	{
	}

	void BanLine::Initialize()
	{
		std::wstring MtKey(mUIKey + L"_LineMt");

#pragma region Meterial Load
		{
			//	Header
			Resources::Load<Texture>(L"BanLine_RedTex", L"..\\Resources\\useResource\\Banpick\\middle_ban_red_line.png");
			Resources::Load<Texture>(L"BanLine_BlueTex", L"..\\Resources\\useResource\\Banpick\\middle_ban_blue_line.png");

			ssz::object::LoadMaterial(MtKey, L"SpriteShader", L"BanLine_BlueTex", eRenderingMode::Transparent);

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
			tr->SetScale(Vector3(1450.f, 90.f, 1.f));
			tr->SetTransType(Transform::eTransType::PosAdd);
		
			Resources::Load<Texture>(L"BanLine_ArrowBlueTex", L"..\\Resources\\useResource\\BanPick\\turn_arrow_icon_0.png");
			Resources::Load<Texture>(L"BanLine_ArrowRedTex", L"..\\Resources\\useResource\\BanPick\\turn_arrow_icon_1.png");
			ssz::object::LoadMaterial(L"BanlineArrow", L"SpriteShader", L"BanLine_ArrowBlueTex", eRenderingMode::Transparent);

			// ArrowMark
			mArrowMark = ssz::object::InstantiateUI<UIObject>(Vector3(-520.f, 0.f, -0.00001f), Vector3(66.f, 63.f, 0.f), this, L"BanLineArrowMark");
			mArrowMark->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"BanlineArrow");
			Transform* ArrowTr = mArrowMark->GetComponent<Transform>();
			ArrowTr->SetParent(tr);
			ArrowTr->SetTransType(Transform::eTransType::PosAdd);
		}
#pragma endregion
#pragma region SlotUI Load
		{

		}
#pragma endregion
	}
	
	void BanLine::Update()
	{
		Transform* ArrowTr = mArrowMark->GetComponent<Transform>();

		if (mCurTeamColor == eTeamColor::Blue)
		{
			//	Blue Team
			float BlueDefaultPos = -630.f;

			Vector3 Pos = ArrowTr->GetPosition();

			float fForce = -(BlueDefaultPos - Pos.x) + 1;

			Pos.x -= fForce * 4.f * (float)Time::DeltaTime();

			// 0부터 80 까지
			if (BlueDefaultPos > Pos.x)
				Pos.x = BlueDefaultPos + 40.f;

			ArrowTr->SetPosition(Pos);
		}
		else if (mCurTeamColor == eTeamColor::Red)
		{
			// Red Team
			float RedDefaultPos = 630.f;

			Vector3 Pos = ArrowTr->GetPosition();

			float fForce = (RedDefaultPos - Pos.x) + 1;

			Pos.x += fForce * 4.f * (float)Time::DeltaTime();

			// 0부터 80 까지
			if (RedDefaultPos < Pos.x)
				Pos.x = RedDefaultPos - 40.f;

			ArrowTr->SetPosition(Pos);
		}

		UIObject::Update();
	}
	
	void BanLine::LateUpdate()
	{
		UIObject::LateUpdate();
	}
	
	void BanLine::ChangeTurn(eTeamColor TeamColor)
	{
		Transform* ArrowTr = mArrowMark->GetComponent<Transform>();

		mCurTeamColor = TeamColor;

		switch (mCurTeamColor)
		{
		case ssz::eTeamColor::Red:
		{
			mArrowMark->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(L"BanLine_ArrowRedTex");
			GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(L"BanLine_RedTex");

			Vector3 Pos = ArrowTr->GetPosition();
			Pos.x = 590.f;
			ArrowTr->SetPosition(Pos);
			
			break;
		}
		case ssz::eTeamColor::Blue:
		{
			mArrowMark->GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(L"BanLine_ArrowBlueTex");
			GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(L"BanLine_BlueTex");

			Vector3 Pos = ArrowTr->GetPosition();
			Pos.x = -590.f;
			ArrowTr->SetPosition(Pos);

			break;
		}
		}

	}
}