#include "sszObj_IG_Stadium.h"
#include "CommonObjHeader.h"

#include "sszObj_Waterfall.h"
#include "sszArrangementScript.h"

namespace ssz
{
	IG_Stadium::IG_Stadium()
	{
	}

	IG_Stadium::~IG_Stadium()
	{
	}

	void IG_Stadium::Initialize()
	{
		Resources::Load<Texture>(L"IGStadiumTex", L"..\\Resources\\useResource\\stadium\\ingame\\stadium.png");
		LoadMaterial(L"IGStadiumMt", L"SpriteShader", L"IGStadiumTex", eRenderingMode::Transparent);

		SetName(L"IG_Stadium");
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"IGStadiumMt");

		float OnwerDepth = GetComponent<Transform>()->GetPosition().z;
		Waterfall* Waterfall_R = Instantiate<Waterfall>(Vector3(0.1012f, -0.3197f, OnwerDepth + 0.0001f), Vector3(0.035f, 0.222f, 1.f), eLayerType::BackGroundObj);
		Waterfall_R->AddComponent<Collider2D>();
		Waterfall* Waterfall_L = Instantiate<Waterfall>(Vector3(-0.1012f, -0.3197f, OnwerDepth + 0.0001f), Vector3(0.035f, 0.222f, 1.f), eLayerType::BackGroundObj);
		Waterfall_L->AddComponent<Collider2D>();

		// Transform ¿¬°á
		Transform* StadiumTr = GetComponent<Transform>();
		Transform* WaterfallRTr = Waterfall_R->GetComponent<Transform>();
		Transform* WaterfallLTr = Waterfall_L->GetComponent<Transform>();
		WaterfallRTr->SetParent(StadiumTr);
		WaterfallLTr->SetParent(StadiumTr);
	}
}