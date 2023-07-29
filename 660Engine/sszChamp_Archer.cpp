#include "sszChamp_Archer.h"
#include "CommonObjHeader.h"

#include "sszScript_Archer.h"
#include "CommonObjHeader.h"

namespace ssz
{
	Champ_Archer::Champ_Archer()
	{
	}

	Champ_Archer::~Champ_Archer()
	{
	}

	void Champ_Archer::Initialize()
	{
		SetChampInfo(eChampType::MARKSMAN, 42, 0.67f, 120, 5, 100, 3); // 챔피언 기본정보입력

		AddComponent<MeshRenderer>();
		AddComponent<Collider2D>();
		AddComponent<Animator>();

		SetAnimator();

		AddComponent<Script_Archer>();
	}

	void Champ_Archer::Update()
	{
		GameObject::Update();
	}

	void Champ_Archer::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Champ_Archer::Render()
	{
		GameObject::Render();
	}

	void Champ_Archer::SetAnimator()
	{
		// Load Atals
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"archer_sprite", L"..\\Resources\\useResource\\ChampSprite\\archer\\archer_sprite\\archer.png");
		
		// Set MeshRenderer
		LoadMaterial(L"archer_spriteMt", L"AnimationShader", L"archer_sprite", eRenderingMode::Transparent);
		GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"archer_spriteMt");
		
		// SetAnimator
		Animator* anim = GetComponent<Animator>();

		anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), Vector2(64.f, 64.f), 4, Vector2(0.f, 0.f), 6.f);
		anim->Create(L"archer_move", L"archer_sprite", Vector2(0.f, 64.f), Vector2(64.f, 64.f), 8, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_attack", L"archer_sprite", Vector2(0.f, 128.f), Vector2(64.f, 64.f), 7, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_dead", L"archer_sprite", Vector2(0.f, 192.f), Vector2(64.f, 64.f), 9, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_skill", L"archer_sprite", Vector2(0.f, 256.f), Vector2(64.f, 64.f), 17, Vector2(0.f, 0.f), 8.f);
		anim->PlayAnimation(L"archer_idle", true);
	}
	
	void Champ_Archer::Attack()
	{
	}
	
	void Champ_Archer::Dead()
	{
	}
}