#include "sszObj_Waterfall.h"
#include "CommonHeader.h"

namespace ssz
{
	Waterfall::Waterfall()
	{
	}

	Waterfall::~Waterfall()
	{
	}

	void Waterfall::Initialize()
	{
		Resources::Load<Texture>(L"WaterfallSprite", L"..\\Resources\\useResource\\stadium\\ingame\\stadium_waterfall_animation.png");
		LoadMaterial(L"WaterfallMt", L"AnimationShader", L"WaterfallSprite", eRenderingMode::Transparent);

		SetName(L"Waterfall");
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"WaterfallMt");

		Animator* anim = AddComponent<Animator>();

		anim->Create(L"WaterfallAnimation", L"WaterfallSprite", Vector2(0.f, 0.f), Vector2(35.f, 222.f), 8, Vector2(0.f, 0.f), 8.f);
		anim->PlayAnimation(L"WaterfallAnimation", true);
	}
}