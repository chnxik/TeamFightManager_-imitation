#include "sszScript_Archer.h"

#include "sszArcherBT.cpp"

#include "sszTGM.h"

#include "sszChamp.h"

#include "sszColObj.h"
#include "sszProjectile.h"

namespace ssz
{
	using namespace AI;

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
		Owner->SetChampInfo(eChampType::eMARKSMAN, 42, 0.67f, 120, 5, 100, 3); // è�Ǿ� ���� �Է�
		Owner->InitChampStatus(0, 0);	// �ΰ��� ���� ����
		
		Owner->SetChampKrName(L"�ü�");
		Owner->SetChampClassType(L"���Ÿ�");
		Owner->SetChampSkillInfo(L"��븦 ������Ű�� ȭ���� �߻��ϸ�\n�ڷ� �� ��¦ �������ϴ�.");
		Owner->SetChampUltInfo(L"������ ���鿡�� ������ ȭ����\n �����մϴ�.");

		std::shared_ptr<Texture> SkillIcon = Resources::Load<Texture>(L"archer_skilliconTex", L"..\\Resources\\useResource\\ChampSprite\\archer\\skillicon\\archer_skill.png");
		std::shared_ptr<Texture> UltIcon = Resources::Load<Texture>(L"archer_ulticonTex", L"..\\Resources\\useResource\\ChampSprite\\archer\\skillicon\\archer_ult.png");
		std::shared_ptr<Texture> SlotTex = Resources::Load<Texture>(L"archer_SlotTex", L"..\\Resources\\useResource\\Banpick\\ChampIcon\\archer.png");

		Owner->SetSkillIcon(SkillIcon);
		Owner->SetUltIcon(UltIcon);
		Owner->SetSlotTex(SlotTex);

		Owner->GetChampStatus()->CoolTime_Skill = 3.0f;

		Owner->GetComponent<Transform>()->SetScale(Vector3(128.f, 128.f, 1.f)); // 64 size
	}

	void Script_Archer::InitChampAnim()
	{
		// Projectile Set
		Resources::Load<Texture>(L"archer_arrow", L"..\\Resources\\useResource\\ChampSprite\\archer\\effect\\arrow.png");
		LoadMaterial(L"archer_arrowMt", L"SpriteShader", L"archer_arrow", eRenderingMode::Transparent);

		// ======================================== ���� �ִϸ��̼� ���� ===========================================

		Champ* Owner = (Champ*)GetOwner();

		// Load Atlas
		std::wstring ChampName = L"archer";							// Ŭ�����̸�
		Owner->SetChampName(ChampName);

		std::wstring AtlasKey = ChampName + L"_sprite";
		std::wstring AtlasPath =
			L"..\\Resources\\useResource\\ChampSprite\\" + ChampName + L"\\" + AtlasKey + L"\\" + ChampName + L".png";

		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(AtlasKey, AtlasPath);

		// Set Mesh Renderer
		std::wstring MtKey = AtlasKey + L"Mt";
		LoadMaterial(MtKey, L"AnimationShader", AtlasKey, eRenderingMode::Transparent);
		Owner->AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

		std::wstring IdleAnikey = ChampName + L"_idle";
		std::wstring MoveAnikey = ChampName + L"_move";
		std::wstring AttackAnikey = ChampName + L"_attack";
		std::wstring DeadAnikey = ChampName + L"_dead";
		std::wstring SkillAnikey = ChampName + L"_skill";
		std::wstring UltAnikey = ChampName + L"_ultimate";

		// Animation Set

		Animator* anim = Owner->AddComponent<Animator>();
		Transform* tr = Owner->GetComponent<Transform>();

		tr->SetScale(Vector3(128.f, 128, 0.f));	// Set Scale
		Vector2 FrmSize(64.f, 64.f);				// frm szie

		// ������, �����Ӽӵ�
		Vector2 IdleAnimInfo	= { 4.f, 10.f };
		Vector2 MoveAnimInfo	= { 8.f, 10.f };
		Vector2 AttackAnimInfo	= { 7.f, 10.f };
		Vector2 DeadAnimInfo	= { 9.f, 10.f };
		Vector2 SkillAnimInfo	= { 17.f, 22.f };
		Vector2 UltAnimInfo		= { 9.f, 22.f };

		anim->Create(IdleAnikey, AtlasKey, Vector2(0.f, 0.f), FrmSize, (int)IdleAnimInfo.x, Vector2(0.f, 0.f), IdleAnimInfo.y);
		anim->Create(MoveAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 1), FrmSize, (int)MoveAnimInfo.x, Vector2(0.f, 0.f), MoveAnimInfo.y);
		anim->Create(AttackAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 2), FrmSize, (int)AttackAnimInfo.x, Vector2(0.f, 0.f), AttackAnimInfo.y);
		anim->Create(DeadAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 3), FrmSize, (int)DeadAnimInfo.x, Vector2(0.f, 0.f), DeadAnimInfo.y);
		anim->Create(SkillAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 4), FrmSize, (int)SkillAnimInfo.x, Vector2(0.f, 0.f), SkillAnimInfo.y);
		anim->Create(UltAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 5), FrmSize, (int)UltAnimInfo.x, Vector2(0.f, 0.f), UltAnimInfo.y);

		Owner->SetAnimKey(Champ::eActiveType::IDLE, IdleAnikey);
		Owner->SetAnimKey(Champ::eActiveType::MOVE, MoveAnikey);
		Owner->SetAnimKey(Champ::eActiveType::ATTACK, AttackAnikey);
		Owner->SetAnimKey(Champ::eActiveType::DEAD, DeadAnikey);
		Owner->SetAnimKey(Champ::eActiveType::SKILL, SkillAnikey);
		Owner->SetAnimKey(Champ::eActiveType::ULTIMATE, UltAnikey);

		// ===================================================================================
		
		
		// ==== Animation Event Set ====

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

		std::wstring ChampName = Owner->GetChampName();
		
		std::wstring IdleAnikey = ChampName + L"_idle";
		std::wstring MoveAnikey = ChampName + L"_move";
		std::wstring AttackAnikey = ChampName + L"_attack";
		std::wstring DeadAnikey = ChampName + L"_dead";
		std::wstring SkillAnikey = ChampName + L"_skill";
		std::wstring UltAnikey = ChampName + L"_ultimate";

		Resources::Load<AudioClip>(AttackAnikey, L"..\\Resources\\useResource\\Audio\\Bow_fast.wav");
		Resources::Load<AudioClip>(SkillAnikey, L"..\\Resources\\useResource\\Audio\\Bow_fast.wav");
		Resources::Load<AudioClip>(DeadAnikey, L"..\\Resources\\useResource\\Audio\\Body_Drop.wav");
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