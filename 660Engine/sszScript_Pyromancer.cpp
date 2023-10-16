#include "sszScript_Pyromancer.h"

#include "sszPyromancerBT.cpp"

#include "sszTGM.h"

#include "sszChamp.h"

#include "sszColObj.h"
#include "sszProjectile.h"
#include "sszEffect.h"

namespace ssz
{
	using namespace AI;

	Script_Pyromancer::Script_Pyromancer()
	{
	}

	Script_Pyromancer::~Script_Pyromancer()
	{
	}

	void Script_Pyromancer::Initialize()
	{
		InitChampInfo();
		InitChampAnim();
		InitAudio();
		InitColObj();
		InitBT();
	}

	void Script_Pyromancer::Update()
	{
		GetRootNode()->Run();
	}

	void Script_Pyromancer::InitChampInfo()
	{
		Champ* Owner = (Champ*)GetOwner();

		Owner->SetName(PYROMANCER); // è�� �̸� �Է�
		Owner->SetChampInfo(eChampType::eMAGE, 45, 0.5f, 100, 3, 80, 3); // è�Ǿ� ���� �Է�
		Owner->InitChampStatus(0, 0);	// �ΰ��� ���� ����

		Owner->SetChampKrName(L"ȭ������");
		Owner->SetChampClassType(L"������");
		Owner->SetChampSkillInfo(L"������ �����ϴ� ȭ�� ������ ��ȯ�մϴ�.");
		Owner->SetChampUltInfo(L"�ֺ� ���� ������ ���������� ���ظ� ���ϴ� ������ �����մϴ�.");

		std::shared_ptr<Texture> SkillIcon = Resources::Load<Texture>(L"pyromancer_skilliconTex", L"..\\Resources\\useResource\\ChampSprite\\pyromancer\\skillicon\\pyromancer_skill.png");
		std::shared_ptr<Texture> UltIcon = Resources::Load<Texture>(L"pyromancer_ulticonTex", L"..\\Resources\\useResource\\ChampSprite\\pyromancer\\skillicon\\pyromancer_ult.png");
		std::shared_ptr<Texture> SlotTex = Resources::Load<Texture>(L"pyromancer_SlotTex", L"..\\Resources\\useResource\\Banpick\\ChampIcon\\pyromancer.png");

		Owner->SetSkillIcon(SkillIcon);
		Owner->SetUltIcon(UltIcon);
		Owner->SetSlotTex(SlotTex);

		Owner->GetChampStatus()->CoolTime_Skill = 6.5f;

		Owner->GetComponent<Transform>()->SetScale(Vector3(170.f, 170.f, 1.f)); // 64 : 128, 96 : 170
	}

	void Script_Pyromancer::InitChampAnim()
	{
		// ======================================== ���� �ִϸ��̼� ���� ===========================================

		Champ* Owner = (Champ*)GetOwner();

		// Load Atlas
		std::wstring ChampName = L"pyromancer";							// Ŭ�����̸�
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

		tr->SetScale(Vector3(170.f, 170.f, 0.f));	// Set Scale
		Vector2 FrmSize(96.f, 96.f);				// frm szie

		// ������, �����Ӽӵ�
		Vector2 IdleAnimInfo = { 5.f, 10.f };
		Vector2 MoveAnimInfo = { 4.f, 10.f };
		Vector2 AttackAnimInfo = { 8.f, 10.f };
		Vector2 DeadAnimInfo = { 8.f, 10.f };
		Vector2 SkillAnimInfo = { 4.f, 10.f };
		Vector2 UltAnimInfo = { 13.f, 10.f };

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

		anim->StartEvent(Owner->GetAnimKey(Champ::eActiveType::ATTACK)) = std::bind(&Script_Pyromancer::Attack, this);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::ATTACK)) = std::bind(&Script_Pyromancer::AttackComplete, this);
		anim->StartEvent(Owner->GetAnimKey(Champ::eActiveType::SKILL)) = std::bind(&Script_Pyromancer::Skill, this);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::DEAD)) = std::bind(&BattleManager::RegistRespawnPool, Owner);

		Owner->Play_Idle();
	}

	void Script_Pyromancer::InitColObj()
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

	void Script_Pyromancer::InitAudio()
	{
		Champ* Owner = (Champ*)GetOwner();
		AudioSource* As = Owner->AddComponent<AudioSource>();
		Resources::Load<AudioClip>(L"knight_attack", L"..\\Resources\\useResource\\Audio\\Sword_Woosh_1.wav");
		Resources::Load<AudioClip>(L"knight_dead", L"..\\Resources\\useResource\\Audio\\Body_Drop.wav");
	}

	void Script_Pyromancer::InitBT()
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
		// Seq_AttackAnim->AddChild<Act_Attack_Knight>();	// 2-2-2-3-3-1 ���� �ִϸ��̼� �ݺ����
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

	void Script_Pyromancer::Attack()
	{
	}

	void Script_Pyromancer::Skill()
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

	void Script_Pyromancer::Dead()
	{
	}
}