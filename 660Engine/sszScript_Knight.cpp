#include "sszScript_Knight.h"

// Test
#include "sszCommonBT.cpp"

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

		Owner->SetChampInfo(eChampType::FIGHTER, 21, 0.67f, 37, 10, 200, 5);
		Owner->InitChampStatus(0, 0);

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

		anim->Create(L"knight_idle", L"knight_sprite", Vector2(0.f, 0.f), FrmSize, 5, Vector2(0.f, 0.f), 9.f);
		anim->Create(L"knight_move", L"knight_sprite", Vector2(0.f, FrmSize.y * 1), FrmSize, 8, Vector2(0.f, 0.f), 9.f);
		anim->Create(L"knight_attack", L"knight_sprite", Vector2(0.f, FrmSize.y * 2), FrmSize, 7, Vector2(0.f, 0.f), 9.f);
		anim->Create(L"knight_dead", L"knight_sprite", Vector2(0.f, FrmSize.y * 3), FrmSize, 9, Vector2(0.f, 0.f), 9.f);
		anim->Create(L"knight_skill1", L"knight_sprite", Vector2(0.f, FrmSize.y * 4), FrmSize, 7, Vector2(0.f, 0.f), 9.f);
		anim->Create(L"knight_skill2", L"knight_sprite", Vector2(0.f, FrmSize.y * 5), FrmSize, 7, Vector2(0.f, 0.f), 9.f);

		Owner->SetAnimKey(Champ::eActiveType::IDLE, L"knight_idle");
		Owner->SetAnimKey(Champ::eActiveType::MOVE, L"knight_move");
		Owner->SetAnimKey(Champ::eActiveType::ATTACK, L"knight_attack");
		Owner->SetAnimKey(Champ::eActiveType::DEAD, L"knight_dead");
		Owner->SetAnimKey(Champ::eActiveType::SKILL, L"knight_skill1");
		Owner->SetAnimKey(Champ::eActiveType::ULTIMATE, L"knight_skill2");
		
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::ATTACK)) = std::bind(&Champ::ATTACK, Owner);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::DEAD)) = std::bind(&BattleManager::RegistRespawnPool, Owner);

		Owner->Play_Idle();
	}

	void Script_Knight::InitColObj()
	{
		Champ* Owner = (Champ*)GetOwner();

		// Champ Collider
		Vector3 ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(64.f, 74.f, 1.f);

		Collider2D* Col = Owner->AddComponent<Collider2D>();
		Col->SetOffsetSize(ColScale);
		Col->SetOffsetPos(Vector3(0.f, 10.f, 0.f));

		ColObj* ATKCOL = Owner->CreateColObj(eColObjType::RANGE);

		Transform* AtkColTr = ATKCOL->GetComponent<Transform>();
		AtkColTr->SetParent(Owner->GetComponent<Transform>()); // 부모를 따라다니는 ColObj
		Collider2D* AttackArea = ATKCOL->GetComponent<Collider2D>();
		AttackArea->SetType(eColliderType::Circle);

		float Rng = Owner->GetChampInfo().RNG * 2.f;
		ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(Rng, Rng, 1.f);
		AttackArea->SetOffsetSize(ColScale);

		AttackArea->SetOffsetPos(Vector3(0.f, 10.f, 0.f));
	}

	void Script_Knight::InitAudio()
	{
		Champ* Owner = (Champ*)GetOwner();
	}

	void Script_Knight::InitBT()
	{
		std::shared_ptr<AIBB> BB = InstantiateAIBB();

		// [1] 최상위 셀렉터 노드
		Selector_Node* ChampBT = CreateRootNode(BB)->AddChild<Selector_Node>();

		// [2-1] 사망 판단 시퀀스
		Sequence_Node* Seq_Dead = ChampBT->AddChild<Sequence_Node>();
		Seq_Dead->AddChild<Con_IsAlive>(); // 2-1-1 사망 애니메이션 확인

		// [2-2] 상호작용(공격,스킬,궁극기) 판단 시퀀스
		Sequence_Node* Seq_Active = ChampBT->AddChild<Sequence_Node>();
		Seq_Active->AddChild<Con_SerchTarget_Enemy_Near>();	// 2-2-1 타겟 지정 여부 (거리)

		Selector_Node* Sel_SelectActive = Seq_Active->AddChild<Selector_Node>(); // 2-2-2 Active 방식 선택
		// Sequence_Node* Seq_Active_Ultimate = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-1 궁극기
		// Sequence_Node* Seq_Active_Skill = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-2 스킬

		Sequence_Node* Seq_Active_Attack = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-3 기본공격
		Seq_Active_Attack->AddChild<Con_CheckActive_Attack_CoolTime>();	// 2-2-2-3-1 기본공격 대기시간 판단
		Seq_Active_Attack->AddChild<Con_CheckRagne_Attack>();	// 2-2-2-3-1 기본공격 사거리 판단
		Seq_Active_Attack->AddChild<Act_SetDir_Target>(); // 2-2-2-3-2 타겟방향으로 방향전환

		Sequence_Node* Seq_AttackAnim = Seq_Active_Attack->AddChild<Sequence_Node>(); // 2-2-2-3-3 공격 애니메이션
		Seq_AttackAnim->AddChild<Act_PlayAnim_Attack>();	// 2-2-2-3-3-1 공격 애니메이션 반복재생
		Seq_AttackAnim->AddChild<Act_PlayAnim_Idle>();		// 2-2-2-3-3-2 공격애니메이션 종료시 Idle로 초기화

		// [2-3] 이동 판단 시퀀스
		Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>();
		Selector_Node* Sel_MovePoint = Seq_Move->AddChild<Selector_Node>(); // 2-3-1 이동지점 갱신 판단
		Sel_MovePoint->AddChild<Con_IsArrive>();			// 2-3-1-1 목표지점 도착 판단
		// Sel_MovePoint->AddChild<Act_SetMovePoint_Kiting>();	// 2-3-1-2 카이팅 이동 지점
		Sel_MovePoint->AddChild<Act_SetMovePoint_Random>();	// 2-3-1-3 랜덤 이동 지점

		Seq_Move->AddChild<Act_SetDir_MovePoint>();		// 2-3-2-1 이동방향으로 방향전환
		Seq_Move->AddChild<Act_Move_Default>();			// 2-3-2-2 이동방향으로 이동
		Seq_Move->AddChild<Act_PlayAnim_Move>();		// 2-3-2-3 이동애니메이션 재생
	}

	void Script_Knight::Dead()
	{
	}

}