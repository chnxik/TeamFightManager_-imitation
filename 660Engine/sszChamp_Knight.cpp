#include "sszChamp_Knight.h"
#include "CommonObjHeader.h"

#include "sszScript_Knight.h"

namespace ssz
{
	Champ_Knight::Champ_Knight()
		: mATKArea(nullptr)
	{
	}

	Champ_Knight::~Champ_Knight()
	{
	}
	
	void Champ_Knight::Initialize()
	{
		SetName(L"Champ_Knight");

		SetChampInfo(eChampType::FIGHTER, 21, 0.67f, 37, 60, 200, 5);

		GetComponent<Transform>()->SetScale(Vector3(170.f, 170.f, 1.f)); // 96 size

		// Champ Collider
		Vector3 ColScale = -GetComponent<Transform>()->GetScale() + Vector3(64.f, 74.f, 1.f);

		Collider2D* Col = AddComponent<Collider2D>();
		Col->SetOffsetSize(ColScale);
		Col->SetOffsetPos(Vector3(0.f, 10.f, 0.f));


		// Create Champ ColObj
		mATKArea = CreateColObj(L"AttackArea");

		Transform* AtkColTr = mATKArea->GetComponent<Transform>();
		AtkColTr->SetParent(GetComponent<Transform>()); // 부모를 따라다니는 ColObj
		Collider2D* AttackArea = mATKArea->GetComponent<Collider2D>();
		AttackArea->SetType(eColliderType::Circle);
		
		float Rng = GetChampInfo().RNG * 2.f;
		ColScale = -GetComponent<Transform>()->GetScale() + Vector3(Rng, Rng, 1.f);
		AttackArea->SetOffsetSize(ColScale);
		
		AttackArea->SetOffsetPos(Vector3(0.f, 10.f, 0.f));
		
		
		AddComponent<MeshRenderer>();
		AddComponent<Animator>();

		SetAnimator();

		AddComponent<Script_Knight>();
	}
	
	void Champ_Knight::Update()
	{
		GameObject::Update();
	}
	
	void Champ_Knight::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	
	void Champ_Knight::Render()
	{
		GameObject::Render();
	}
	
	void Champ_Knight::SetAnimator()
	{
		// Load Atlas
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"knight_sprite", L"..\\Resources\\useResource\\ChampSprite\\knight\\knight_sprite\\knight.png");
		
		// Set MeshRenderer
		LoadMaterial(L"knight_spriteMt", L"AnimationShader", L"knight_sprite", eRenderingMode::Transparent);
		GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"knight_spriteMt");

		//SetAnimator
		Animator* anim = GetComponent<Animator>();

		Vector2 FrmSize(96.f, 96.f);

		anim->Create(L"knight_idle", L"knight_sprite", Vector2(0.f, 0.f), FrmSize, 5, Vector2(0.f, 0.f), 6.f);
		anim->Create(L"knight_move", L"knight_sprite", Vector2(0.f, FrmSize.y * 1), FrmSize, 8, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_attack", L"knight_sprite", Vector2(0.f, FrmSize.y * 2), FrmSize, 7, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_dead", L"knight_sprite", Vector2(0.f, FrmSize.y * 3), FrmSize, 9, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_skill1", L"knight_sprite", Vector2(0.f, FrmSize.y * 4), FrmSize, 7, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_skill2", L"knight_sprite", Vector2(0.f, FrmSize.y * 5), FrmSize, 7, Vector2(0.f, 0.f), 8.f);
		Play_Idle();
	}

	void Champ_Knight::Play_Idle()
	{
		GetComponent<Animator>()->PlayAnimation(L"knight_idle", true);
	}

	void Champ_Knight::Play_Move()
	{
		GetComponent<Animator>()->PlayAnimation(L"knight_move", true);
	}

	void Champ_Knight::Play_Attack()
	{
		GetComponent<Animator>()->PlayAnimation(L"knight_attack", false);
	}

	void Champ_Knight::Play_Dead()
	{
		GetComponent<Animator>()->PlayAnimation(L"knight_dead", false);
	}

	void Champ_Knight::Play_Skill1()
	{
		GetComponent<Animator>()->PlayAnimation(L"knight_skill1", true);
	}

	void Champ_Knight::Play_Skill2()
	{
		GetComponent<Animator>()->PlayAnimation(L"knight_skill2", true);
	}
}