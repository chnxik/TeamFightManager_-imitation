#include "sszScript_Knight.h"

// Test
#include "sszKnightBT.cpp"

namespace ssz
{
	Script_Knight::Script_Knight()
	{
	}

	Script_Knight::~Script_Knight()
	{
	}

	void Script_Knight::Initialize()
	{
		InitChampInfo();
		InitChampAnim();
		InitAudio();
		InitColObj();
		InitBT();
	}

	void Script_Knight::Update()
	{
		GetRootNode()->Run();
	}

	void Script_Knight::InitChampInfo()
	{
		Champ* Owner = (Champ*)GetOwner();

		Owner->SetName(KNIGHT);

		Owner->SetChampInfo(eChampType::eFIGHTER, 21, 0.67f, 37, 10, 200, 5);
		Owner->InitChampStatus(0, 0);

		Owner->GetChampStatus()->CoolTime_Skill = 4.2f;

		Owner->GetComponent<Transform>()->SetScale(Vector3(170.f, 170.f, 1.f)); // 96 size
	}

	void Script_Knight::InitChampAnim()
	{
		Champ* Owner = (Champ*)GetOwner();

		Owner->AddComponent<MeshRenderer>();
		Owner->AddComponent<Animator>();

		// Load Atlas
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"knight_sprite", L"..\\Resources\\useResource\\ChampSprite\\knight\\knight_sprite\\knight.png");

		// Set MeshRenderer
		LoadMaterial(L"knight_spriteMt", L"AnimationShader", L"knight_sprite", eRenderingMode::Transparent);
		Owner->GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"knight_spriteMt");

		//SetAnimator
		Animator* anim = Owner->GetComponent<Animator>();

		Vector2 FrmSize(96.f, 96.f);

		anim->Create(L"knight_idle", L"knight_sprite", Vector2(0.f, 0.f), FrmSize, 5, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"knight_move", L"knight_sprite", Vector2(0.f, FrmSize.y * 1), FrmSize, 8, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"knight_attack", L"knight_sprite", Vector2(0.f, FrmSize.y * 2), FrmSize, 7, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"knight_dead", L"knight_sprite", Vector2(0.f, FrmSize.y * 3), FrmSize, 9, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"knight_skill", L"knight_sprite", Vector2(0.f, FrmSize.y * 4), FrmSize, 7, Vector2(0.f, 0.f), 10.f);
		anim->Create(L"knight_Ultimate", L"knight_sprite", Vector2(0.f, FrmSize.y * 5), FrmSize, 7, Vector2(0.f, 0.f), 10.f);

		Owner->SetAnimKey(Champ::eActiveType::IDLE, L"knight_idle");
		Owner->SetAnimKey(Champ::eActiveType::MOVE, L"knight_move");
		Owner->SetAnimKey(Champ::eActiveType::ATTACK, L"knight_attack");
		Owner->SetAnimKey(Champ::eActiveType::DEAD, L"knight_dead");
		Owner->SetAnimKey(Champ::eActiveType::SKILL, L"knight_skill");
		Owner->SetAnimKey(Champ::eActiveType::ULTIMATE, L"knight_Ultimate");
		
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::ATTACK)) = std::bind(&Champ_Script::AttackComplete, this);
		anim->StartEvent(Owner->GetAnimKey(Champ::eActiveType::SKILL)) = std::bind(&Script_Knight::Skill, this);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::DEAD)) = std::bind(&BattleManager::RegistRespawnPool, Owner);

		Owner->Play_Idle();
	}

	void Script_Knight::InitColObj()
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

	void Script_Knight::InitAudio()
	{
		Champ* Owner = (Champ*)GetOwner();
		AudioSource* As = Owner->AddComponent<AudioSource>();
		Resources::Load<AudioClip>(L"knight_attack", L"..\\Resources\\useResource\\Audio\\Sword_Woosh_1.wav");
		Resources::Load<AudioClip>(L"knight_dead", L"..\\Resources\\useResource\\Audio\\Body_Drop.wav");

	}

	void Script_Knight::InitBT()
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

		Selector_Node* Sel_SelectActive = Seq_Active->AddChild<Selector_Node>(); // 2-2-2 Active ��� ����
		// Sequence_Node* Seq_Active_Ultimate = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-1 �ñر�
		Sequence_Node* Seq_Active_Skill = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-2 ��ų
		Seq_Active_Skill->AddChild<Con_CheckActive_Skill_CoolTime>();	// 2-2-2-2-1 �⺻���� ���ð� �Ǵ�

		Sequence_Node* Seq_SkillAnim = Seq_Active_Skill->AddChild<Sequence_Node>(); // 2-2-2-2-3 ���� �ִϸ��̼�
		Seq_SkillAnim->AddChild<Act_PlayAnim_Skill>();	// 2-2-2-2-3-1 ���� �ִϸ��̼� �ݺ����
		Seq_SkillAnim->AddChild<Act_PlayAnim_Idle>();	// 2-2-2-2-3-2 ���ݾִϸ��̼� ����� Idle�� �ʱ�ȭ

		Sequence_Node* Seq_Active_Attack = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-3 �⺻����
		Seq_Active_Attack->AddChild<Con_CheckActive_Attack_CoolTime>();	// 2-2-2-3-1 �⺻���� ���ð� �Ǵ�
		Seq_Active_Attack->AddChild<Con_CheckRagne_Attack>();	// 2-2-2-3-1 �⺻���� ��Ÿ� �Ǵ�
		Seq_Active_Attack->AddChild<Act_SetDir_Target>(); // 2-2-2-3-2 Ÿ�ٹ������� ������ȯ

		Sequence_Node* Seq_AttackAnim = Seq_Active_Attack->AddChild<Sequence_Node>(); // 2-2-2-3-3 ���� �ִϸ��̼�
		Seq_AttackAnim->AddChild<Act_Attack_Knight>();	// 2-2-2-3-3-1 ���� �ִϸ��̼� �ݺ����
		Seq_AttackAnim->AddChild<Act_PlayAnim_Idle>();		// 2-2-2-3-3-2 ���ݾִϸ��̼� ����� Idle�� �ʱ�ȭ

		// [2-3] �̵� �Ǵ� ������
		Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>();
		Selector_Node* Sel_MovePoint = Seq_Move->AddChild<Selector_Node>(); // 2-3-1 �̵����� ���� �Ǵ�
		Sequence_Node* Seq_Move_Complete = Sel_MovePoint->AddChild<Sequence_Node>();	// 2-3-1-1 ��ǥ���� ���� �Ǵ�
		Seq_Move_Complete->AddChild<Con_IsArrive>();			// 2-3-1-1-1 ��ǥ���� ���� �Ǵ� ����ǳ��
		Sel_MovePoint->AddChild<Act_SetMovePoint_Kiting>();	// 2-3-1-2 ī���� �̵� ����
		Sel_MovePoint->AddChild<Act_SetMovePoint_Random>();	// 2-3-1-3 ���� �̵� ����

		// Seq_Move->AddChild<Act_SetDir_MovePoint>();		// 2-3-2-1 �̵��������� ������ȯ
		Seq_Move->AddChild<Act_Move_Default>();			// 2-3-2-2 �̵��������� �̵�
		Seq_Move->AddChild<Act_PlayAnim_Move>();		// 2-3-2-3 �̵��ִϸ��̼� ���
	}

	void Script_Knight::Skill()
	{
		Champ* Owner = (Champ*)GetOwner();

		Transform* tr = Owner->GetComponent<Transform>();
		Vector3 vPos = tr->GetPosition();
		Vector3 vScale = tr->GetScale();

		vPos.y -= 5.f;

		TGM::GetEffectObj()->Play(vPos, vScale, Owner->GetAnimKey(Champ::eActiveType::SKILL));
		// ��ų���� ����
		// 1�� ���� �޾ƿͼ� Ÿ���� ������ ���� ����
		// ���� Ÿ���� Ÿ���� �������� -> �ƴϸ� ����. �´ٸ� �ٸ� �� ����Ʈ Ž��
		// ������ �ٸ� ���� ���ٸ� �Ѿ��.
		// �Ͻ������� ��� ���� ��� ���� ���ӽð� �ʿ�

		Owner->GetChampStatus()->accTime_Skill = 0.f;
	}

	void Script_Knight::Dead()
	{
	}

}