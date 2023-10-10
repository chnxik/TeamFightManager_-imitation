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
		// ======================================== 공통 애니메이션 세팅 ===========================================

		Champ* Owner = (Champ*)GetOwner();

		// Load Atlas
		std::wstring ChampName = L"knight";							// 클래스이름
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

		// 프레임, 프레임속도
		Vector2 IdleAnimInfo = { 5.f, 10.f };
		Vector2 MoveAnimInfo = { 8.f, 10.f };
		Vector2 AttackAnimInfo = { 7.f, 10.f };
		Vector2 DeadAnimInfo = { 9.f, 10.f };
		Vector2 SkillAnimInfo = { 7.f, 10.f };
		Vector2 UltAnimInfo = { 7.f, 10.f };

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
				
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::ATTACK)) = std::bind(&Champ_Script::AttackComplete, this);
		anim->StartEvent(Owner->GetAnimKey(Champ::eActiveType::SKILL)) = std::bind(&Script_Knight::Skill, this);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eActiveType::DEAD)) = std::bind(&BattleManager::RegistRespawnPool, Owner);

		Owner->Play_Idle();
	}

	void Script_Knight::InitColObj()
	{
		Champ* Owner = (Champ*)GetOwner();

		// 피격 Collider Set
		Vector3 ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(15.f, 15.f, 1.f);

		Collider2D* Col = Owner->AddComponent<Collider2D>();
		Col->SetOffsetSize(ColScale);
		Col->SetOffsetPos(Vector3(0.f, 0.f, 0.f));

		ColObj* ATKCOL = Owner->CreateColObj(eColObjType::RANGE);

		Transform* AtkColTr = ATKCOL->GetComponent<Transform>();
		AtkColTr->SetParent(Owner->GetComponent<Transform>()); // 부모를 따라다니는 ColObj
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
		Sequence_Node* Seq_Active_Skill = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-2 스킬
		Seq_Active_Skill->AddChild<Con_CheckActive_Skill_CoolTime>();	// 2-2-2-2-1 기본공격 대기시간 판단

		Sequence_Node* Seq_SkillAnim = Seq_Active_Skill->AddChild<Sequence_Node>(); // 2-2-2-2-3 공격 애니메이션
		Seq_SkillAnim->AddChild<Act_PlayAnim_Skill>();	// 2-2-2-2-3-1 공격 애니메이션 반복재생
		Seq_SkillAnim->AddChild<Act_PlayAnim_Idle>();	// 2-2-2-2-3-2 공격애니메이션 종료시 Idle로 초기화

		Sequence_Node* Seq_Active_Attack = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-3 기본공격
		Seq_Active_Attack->AddChild<Con_CheckActive_Attack_CoolTime>();	// 2-2-2-3-1 기본공격 대기시간 판단
		Seq_Active_Attack->AddChild<Con_CheckRagne_Attack>();	// 2-2-2-3-1 기본공격 사거리 판단
		Seq_Active_Attack->AddChild<Act_SetDir_Target>(); // 2-2-2-3-2 타겟방향으로 방향전환

		Sequence_Node* Seq_AttackAnim = Seq_Active_Attack->AddChild<Sequence_Node>(); // 2-2-2-3-3 공격 애니메이션
		Seq_AttackAnim->AddChild<Act_Attack_Knight>();	// 2-2-2-3-3-1 공격 애니메이션 반복재생
		Seq_AttackAnim->AddChild<Act_PlayAnim_Idle>();		// 2-2-2-3-3-2 공격애니메이션 종료시 Idle로 초기화

		// [2-3] 이동 판단 시퀀스
		Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>();
		Selector_Node* Sel_MovePoint = Seq_Move->AddChild<Selector_Node>(); // 2-3-1 이동지점 갱신 판단
		Sequence_Node* Seq_Move_Complete = Sel_MovePoint->AddChild<Sequence_Node>();	// 2-3-1-1 목표지점 도착 판단
		Seq_Move_Complete->AddChild<Con_IsArrive>();			// 2-3-1-1-1 목표지점 도착 판단 컨디션노드
		Sel_MovePoint->AddChild<Act_SetMovePoint_Kiting>();	// 2-3-1-2 카이팅 이동 지점
		Sel_MovePoint->AddChild<Act_SetMovePoint_Random>();	// 2-3-1-3 랜덤 이동 지점

		// Seq_Move->AddChild<Act_SetDir_MovePoint>();		// 2-3-2-1 이동방향으로 방향전환
		Seq_Move->AddChild<Act_Move_Default>();			// 2-3-2-2 이동방향으로 이동
		Seq_Move->AddChild<Act_PlayAnim_Move>();		// 2-3-2-3 이동애니메이션 재생
	}

	void Script_Knight::Skill()
	{
		Champ* Owner = (Champ*)GetOwner();

		Transform* tr = Owner->GetComponent<Transform>();
		Vector3 vPos = tr->GetPosition();
		Vector3 vScale = tr->GetScale();

		vPos.y -= 5.f;

		TGM::GetEffectObj()->Play(vPos, vScale, Owner->GetAnimKey(Champ::eActiveType::SKILL));
		// 스킬내용 구현
		// 1개 적을 받아와서 타겟을 강제로 기사로 지정
		// 현재 타겟의 타겟이 본인인지 -> 아니면 도발. 맞다면 다른 적 리스트 탐색
		// 가능한 다른 적이 없다면 넘어간다.
		// 일시적으로 기사 방어력 상승 버프 지속시간 필요

		Owner->GetChampStatus()->accTime_Skill = 0.f;
	}

	void Script_Knight::Dead()
	{
	}

}