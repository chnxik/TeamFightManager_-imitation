#include "sszChamp_Archer.h"
#include "CommonObjHeader.h"

#include "sszScript_Archer.h"

namespace ssz
{
	Champ_Archer::Champ_Archer()
		: mATKArea(nullptr)
	{
	}

	Champ_Archer::~Champ_Archer()
	{
	}

	void Champ_Archer::Initialize()
	{
		SetName(ARCHER);

		SetChampInfo(eChampType::MARKSMAN, 42, 0.67f, 120, 5, 100, 3); // è�Ǿ� �⺻�����Է�
		InitIGInfo(0, 0); // �ΰ������� ����

		GetComponent<Transform>()->SetScale(Vector3(128.f, 128.f, 1.f)); // 64 size
		
		// Champ Collider
		Vector3 ColScale = -GetComponent<Transform>()->GetScale() + Vector3(64.f, 74.f, 1.f);

		Collider2D* Col = AddComponent<Collider2D>();
		Col->SetOffsetSize(ColScale);
		Col->SetOffsetPos(Vector3(0.f, 10.f, 0.f));
		

		// Create Champ Col Obj
		mATKArea = CreateColObj(L"AttackArea");

		Transform* AtkColTr = mATKArea->GetComponent<Transform>();
		AtkColTr->SetParent(GetComponent<Transform>()); // �θ� ����ٴϴ� ColObj
		Collider2D* AttackArea = mATKArea->GetComponent<Collider2D>();
		AttackArea->SetType(eColliderType::Circle);

		float Rng = GetChampInfo().RNG * 2.f;
		ColScale = -GetComponent<Transform>()->GetScale() + Vector3(Rng, Rng, 1.f);
		AttackArea->SetOffsetSize(ColScale);

		AttackArea->SetOffsetPos(Vector3(0.f, 10.f, 0.f));
		
		
		AddComponent<MeshRenderer>();
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

		Vector2 FrmSize(64.f, 64.f);

		anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), FrmSize, 4, Vector2(0.f, 0.f), 6.f);
		anim->Create(L"archer_move", L"archer_sprite", Vector2(0.f, FrmSize.y * 1), FrmSize, 8, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_attack", L"archer_sprite", Vector2(0.f, FrmSize.y * 2), FrmSize, 7, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_dead", L"archer_sprite", Vector2(0.f, FrmSize.y * 3), FrmSize, 9, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_skill", L"archer_sprite", Vector2(0.f, FrmSize.y * 4), FrmSize, 17, Vector2(0.f, 0.f), 8.f);
		Play_Idle();
	}

	void Champ_Archer::Play_Idle()
	{
		GetComponent<Animator>()->PlayAnimation(L"archer_idle", true);
	}

	void Champ_Archer::Play_Move()
	{
		GetComponent<Animator>()->PlayAnimation(L"archer_move", true);
	}

	void Champ_Archer::Play_Attack()
	{
		GetComponent<Animator>()->PlayAnimation(L"archer_attack", false);
	}

	void Champ_Archer::Play_Dead()
	{
		GetComponent<Animator>()->PlayAnimation(L"archer_dead", false);
	}

	void Champ_Archer::Play_Skill1()
	{
		GetComponent<Animator>()->PlayAnimation(L"archer_skill", true);
	}
}