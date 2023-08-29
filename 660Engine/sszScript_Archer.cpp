#include "sszScript_Archer.h"

// Test
#include "sszArcherBT.cpp"

namespace ssz
{
	Script_Archer::Script_Archer()
	{
	}

	Script_Archer::~Script_Archer()
	{
	}

	void Script_Archer::Initialize()
	{
		InitChampInfo();
		InitChampAnim();
		InitAudio();
		InitColObj();
		InitBT();
	}

	void Script_Archer::Update()
	{
		GetRootNode()->Run();
	}

	void Script_Archer::InitChampInfo()
	{
		Champ* Owner = (Champ*)GetOwner();
		
		Owner->SetName(ARCHER); // è�� �̸� �Է�
		Owner->SetChampInfo(eChampType::MARKSMAN, 42, 0.67f, 120, 5, 100, 4); // è�Ǿ� ���� �Է�
		Owner->InitChampStatus(0, 0);	// �ΰ��� ���� ����

		Owner->GetChampStatus()->CoolTime_Skill = 3.0f;

		Owner->GetComponent<Transform>()->SetScale(Vector3(128.f, 128.f, 1.f)); // 64 size
	}

	void Script_Archer::InitChampAnim()
	{
		Champ* Owner = (Champ*)GetOwner();

		Owner->AddComponent<MeshRenderer>();

		// Projectile Set
		Resources::Load<Texture>(L"archer_arrow", L"..\\Resources\\useResource\\ChampSprite\\archer\\effect\\arrow.png");
		LoadMaterial(L"archer_arrowMt", L"SpriteShader", L"archer_arrow", eRenderingMode::Transparent);

		// Load Atals
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"archer_sprite", L"..\\Resources\\useResource\\ChampSprite\\archer\\archer_sprite\\archer.png");

		// Set MeshRenderer
		LoadMaterial(L"archer_spriteMt", L"AnimationShader", L"archer_sprite", eRenderingMode::Transparent);
		Owner->GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"archer_spriteMt");

		// SetAnimator
		Animator* anim = Owner->AddComponent<Animator>();

		Vector2 FrmSize(64.f, 64.f);


		anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), FrmSize, 4, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"archer_move", L"archer_sprite", Vector2(0.f, FrmSize.y * 1), FrmSize, 8, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"archer_attack", L"archer_sprite", Vector2(0.f, FrmSize.y * 2), FrmSize, 7, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"archer_dead", L"archer_sprite", Vector2(0.f, FrmSize.y * 3), FrmSize, 9, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"archer_skill", L"archer_sprite", Vector2(0.f, FrmSize.y * 4), FrmSize, 17, Vector2(0.f, 0.f), 22.f);
		

		Owner->SetAnimKey(Champ::eActiveType::IDLE,L"archer_idle");
		Owner->SetAnimKey(Champ::eActiveType::MOVE,L"archer_move");
		Owner->SetAnimKey(Champ::eActiveType::ATTACK,L"archer_attack");
		Owner->SetAnimKey(Champ::eActiveType::DEAD,L"archer_dead");
		Owner->SetAnimKey(Champ::eActiveType::SKILL,L"archer_skill");
		
		anim->StartEvent(Owner->GetAnimKey(Champ::eActiveType::ATTACK)) = std::bind(&Script_Archer::Attack, this);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::ATTACK)) = std::bind(&Script_Archer::AttackComplete, this);
		anim->StartEvent(Owner->GetAnimKey(Champ::eActiveType::SKILL)) = std::bind(&Script_Archer::Skill, this);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::DEAD)) = std::bind(&BattleManager::RegistRespawnPool, Owner);
		
		Owner->Play_Idle();
	}

	void Script_Archer::InitColObj()
	{
		Champ* Owner = (Champ*)GetOwner();

		// �ǰ� Collider Set
		Vector3 ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(15.f, 15.f, 1.f);

		Collider2D* Col = Owner->AddComponent<Collider2D>();
		Col->SetOffsetSize(ColScale);
		Col->SetOffsetPos(Vector3(0.f, 0.f, 0.f));

		ColObj* ATKCOL = Owner->CreateColObj(eColObjType::RANGE);

		Transform* AtkColTr = ATKCOL->GetComponent<Transform>();
		AtkColTr->SetParent(Owner->GetComponent<Transform>()); // �θ� ����ٴϴ� ColObj
		Collider2D* AttackArea = ATKCOL->GetComponent<Collider2D>();
		AttackArea->SetType(eColliderType::Circle);

		float Rng = Owner->GetChampInfo().RNG * 2.5f;
		ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(Rng, Rng, 1.f);
		AttackArea->SetOffsetSize(ColScale);

		AttackArea->SetOffsetPos(Vector3(0.f, 10.f, 0.f));
	}

	void Script_Archer::InitAudio()
	{
		Champ* Owner = (Champ*)GetOwner();
		AudioSource* As = Owner->AddComponent<AudioSource>();
		Resources::Load<AudioClip>(L"archer_attack", L"..\\Resources\\useResource\\Audio\\Bow_fast.wav");
		Resources::Load<AudioClip>(L"archer_skill", L"..\\Resources\\useResource\\Audio\\Bow_fast.wav");
		Resources::Load<AudioClip>(L"archer_dead", L"..\\Resources\\useResource\\Audio\\Body_Drop.wav");
	}

	void Script_Archer::InitBT()
	{
		std::shared_ptr<AIBB> BB = InstantiateAIBB();

		// [1] �ֻ��� ������ ���
		Selector_Node* ChampBT = CreateRootNode(BB)->AddChild<Selector_Node>(); 

		// [2-1] ��� �Ǵ� ������
		Sequence_Node* Seq_Dead = ChampBT->AddChild<Sequence_Node>();
		Seq_Dead->AddChild<Con_IsAlive>(); // 2-1-1 ��� �ִϸ��̼� Ȯ��

		// [2-2] ��ȣ�ۿ�(����,��ų,�ñر�) �Ǵ� ������
		Sequence_Node* Seq_Active = ChampBT->AddChild<Sequence_Node>();
		Seq_Active->AddChild<Con_SerchTarget_Enemy_Near>();	// 2-2-1 Ÿ�� ���� ���� (�Ÿ�)
		Seq_Active->AddChild<Con_Retreat_Dist>();			// 2-2-2 ī���� �Ǵ� ( �������Ÿ� �ȿ� �ִ��� )
		
		Selector_Node* Sel_SelectActive = Seq_Active->AddChild<Selector_Node>(); // 2-2-2 Active ��� ����
		// Sequence_Node* Seq_Active_Ultimate = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-1 �ñر�
		Sequence_Node* Seq_Active_Skill = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-2 ��ų
		Seq_Active_Skill->AddChild<Con_CheckActive_Skill_CoolTime>();	// 2-2-2-2-1 �⺻���� ���ð� �Ǵ�
		Seq_Active_Skill->AddChild<Con_CheckRagne_Attack>();	// 2-2-2-2-2 ��ų ��Ÿ� �Ǵ�
		Seq_Active_Skill->AddChild<Act_SetDir_Target>(); // 2-2-2-2-3 Ÿ�ٹ������� ������ȯ

		Sequence_Node* Seq_SkillAnim= Seq_Active_Skill->AddChild<Sequence_Node>(); // 2-2-2-2-3 ���� �ִϸ��̼�
		Seq_SkillAnim->AddChild<Act_Skill_Archer>();	// 2-2-2-2-3-1 ���� �ִϸ��̼� �ݺ����
		Seq_SkillAnim->AddChild<Act_PlayAnim_Idle>();	// 2-2-2-2-3-2 ���ݾִϸ��̼� ����� Idle�� �ʱ�ȭ


		Sequence_Node* Seq_Active_Attack = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-3 �⺻����
		Seq_Active_Attack->AddChild<Con_CheckActive_Attack_CoolTime>();	// 2-2-2-3-1 �⺻���� ���ð� �Ǵ�
		Seq_Active_Attack->AddChild<Con_CheckRagne_Attack>();	// 2-2-2-3-1 �⺻���� ��Ÿ� �Ǵ�
		Seq_Active_Attack->AddChild<Act_SetDir_Target>(); // 2-2-2-3-2 Ÿ�ٹ������� ������ȯ
		
		Sequence_Node* Seq_AttackAnim = Seq_Active_Attack->AddChild<Sequence_Node>(); // 2-2-2-3-3 ���� �ִϸ��̼�
		Seq_AttackAnim->AddChild<Act_PlayAnim_Attack>();	// 2-2-2-3-3-1 ���� �ִϸ��̼� �ݺ����
		Seq_AttackAnim->AddChild<Act_PlayAnim_Idle>();		// 2-2-2-3-3-2 ���ݾִϸ��̼� ����� Idle�� �ʱ�ȭ

		// [2-3] �̵� �Ǵ� ������
		Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>();
		Selector_Node* Sel_MovePoint = Seq_Move->AddChild<Selector_Node>(); // 2-3-1 �̵����� ���� �Ǵ�
		Sel_MovePoint->AddChild<Con_IsArrive>();			// 2-3-1-1 ��ǥ���� ���� �Ǵ�
		Sel_MovePoint->AddChild<Act_SetMovePoint_Kiting>();	// 2-3-1-2 ī���� �̵� ����
		Sel_MovePoint->AddChild<Act_SetMovePoint_Random>();	// 2-3-1-3 ���� �̵� ����

		// Seq_Move->AddChild<Act_SetDir_MovePoint>();		// 2-3-2-1 �̵��������� ������ȯ
		Seq_Move->AddChild<Act_Move_Default>();			// 2-3-2-2 �̵��������� �̵�
		Seq_Move->AddChild<Act_PlayAnim_Move>();		// 2-3-2-3 �̵��ִϸ��̼� ���
	}

	void Script_Archer::Attack()
	{
		Champ* Owner = (Champ*)GetOwner();

		if (Owner->GetTarget_Enemy() != nullptr)
		{
			TGM::GetProjectile()->Shoot(Owner, Owner->GetTarget_Enemy(), Vector3(40.f, 20.f, 1.f), L"archer_arrowMt", Owner->GetChampInfo().ATK);
		}
	}

	void Script_Archer::Skill()
	{
		Champ* Owner = (Champ*)GetOwner();

		if (Owner->GetTarget_Enemy() != nullptr)
		{
			TGM::GetProjectile()->Shoot(Owner, Owner->GetTarget_Enemy(), Vector3(40.f, 20.f, 1.f), L"archer_arrowMt", Owner->GetChampInfo().ATK);
		}

		Owner->GetChampStatus()->accTime_Skill = 0.f;
	}

	void Script_Archer::Dead()
	{
	}
}