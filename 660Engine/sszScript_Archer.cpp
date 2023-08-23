#include "sszScript_Archer.h"
#include "sszTGM.h"
// Test
#include "sszTestBT.cpp"

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
		
		Owner->SetName(ARCHER); // 챔프 이름 입력
		Owner->SetChampInfo(eChampType::MARKSMAN, 42, 0.67f, 120, 5, 100, 3); // 챔피언 정보 입력
		Owner->InitIGInfo(0, 0);	// 인게임 정보 세팅

		Owner->GetComponent<Transform>()->SetScale(Vector3(128.f, 128.f, 1.f)); // 64 size
	}

	void Script_Archer::InitChampAnim()
	{
		Champ* Owner = (Champ*)GetOwner();

		Owner->AddComponent<MeshRenderer>();
		Owner->AddComponent<Animator>();

		// Load Atals
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"archer_sprite", L"..\\Resources\\useResource\\ChampSprite\\archer\\archer_sprite\\archer.png");

		// Set MeshRenderer
		LoadMaterial(L"archer_spriteMt", L"AnimationShader", L"archer_sprite", eRenderingMode::Transparent);
		Owner->GetComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"archer_spriteMt");

		// SetAnimator
		Animator* anim = Owner->GetComponent<Animator>();

		Vector2 FrmSize(64.f, 64.f);


		anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), FrmSize, 4, Vector2(0.f, 0.f), 6.f);
		anim->Create(L"archer_move", L"archer_sprite", Vector2(0.f, FrmSize.y * 1), FrmSize, 8, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_attack", L"archer_sprite", Vector2(0.f, FrmSize.y * 2), FrmSize, 7, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_dead", L"archer_sprite", Vector2(0.f, FrmSize.y * 3), FrmSize, 9, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"archer_skill", L"archer_sprite", Vector2(0.f, FrmSize.y * 4), FrmSize, 17, Vector2(0.f, 0.f), 8.f);
		

		Owner->SetAnimKey(Champ::eAnimType::IDLE,L"archer_idle");
		Owner->SetAnimKey(Champ::eAnimType::MOVE,L"archer_move");
		Owner->SetAnimKey(Champ::eAnimType::ATTACK,L"archer_attack");
		Owner->SetAnimKey(Champ::eAnimType::DEAD,L"archer_dead");
		Owner->SetAnimKey(Champ::eAnimType::SKILL1,L"archer_skill");
		
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eAnimType::ATTACK)) = std::bind(&Champ::Battle, Owner);
		anim->CompleteEvent(Owner->GetAnimKey(Champ::eAnimType::DEAD)) = std::bind(&BattleManager::RegistRespawnPool, Owner);
		
		Owner->Play_Idle();
	}

	void Script_Archer::InitColObj()
	{
		Champ* Owner = (Champ*)GetOwner();

		Vector3 ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(64.f, 74.f, 1.f);

		Collider2D* Col = Owner->AddComponent<Collider2D>();
		Col->SetOffsetSize(ColScale);
		Col->SetOffsetPos(Vector3(0.f, 10.f, 0.f));

		ColObj* ATKCOL = Owner->CreateColObj(eColObjType::ATKAREA);

		Transform* AtkColTr = ATKCOL->GetComponent<Transform>();
		AtkColTr->SetParent(Owner->GetComponent<Transform>()); // 부모를 따라다니는 ColObj
		Collider2D* AttackArea = ATKCOL->GetComponent<Collider2D>();
		AttackArea->SetType(eColliderType::Circle);

		float Rng = Owner->GetChampInfo().RNG * 2.f;
		ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(Rng, Rng, 1.f);
		AttackArea->SetOffsetSize(ColScale);

		AttackArea->SetOffsetPos(Vector3(0.f, 10.f, 0.f));
	}

	void Script_Archer::InitAudio()
	{
		Champ* Owner = (Champ*)GetOwner();
	}

	void Script_Archer::InitBT()
	{
		std::shared_ptr<AIBB> ptrAIBB = std::make_shared<AIBB>();

		ptrAIBB->AddData<std::wstring>(CHAMPKEY, &(GetOwner()->GetName()));

		ptrAIBB->AddData<GameObject>(GetOwner()->GetName(), GetOwner());

		GameObject* pCsr = TGM::GetCursor();
		ptrAIBB->AddData<GameObject>(L"Cursor", pCsr);

		int* CenterPos = ptrAIBB->CreateData<int>(L"CenterPos");
		*CenterPos = -100;

		// Set BT
		Selector_Node* ChampBT = CreateRootNode(ptrAIBB)->AddChild<Selector_Node>(); // 최상위 셀렉터 노드


		Sequence_Node* Seq_Dead = ChampBT->AddChild<Sequence_Node>(); // 사망 판단 시퀀스
		Sequence_Node* Seq_Stop = ChampBT->AddChild<Sequence_Node>(); // 정지 판단 시퀀스
		Selector_Node* Sel_AttackOrBack = ChampBT->AddChild<Selector_Node>(); // 공격 판단 시퀀스
		Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>(); // 이동 판단 시퀀스

		// 사망 판단 시퀀스
		// Seq_Dead->AddChild<Con_CollisionCsr>(); // Csr 충돌 판단
		Seq_Dead->AddChild<Con_IsDead>();
		// Seq_Dead->AddChild<Act_PlayAnim_Dead>(); // Idle Animation 재생

		// 정지 판단 시퀀스
		Seq_Stop->AddChild<Con_IsStopBtnPush>(); // 정지 버튼 입력 판단
		Seq_Stop->AddChild<Act_PlayAnim_Idle>(); // Idle Animation 재생


		// 공격 판단 시퀀스
		Sequence_Node* Seq_Attack = Sel_AttackOrBack->AddChild<Sequence_Node>();

		Seq_Attack->AddChild<Con_CollisionOtehrChamp>();
		Seq_Attack->AddChild<Con_MustBack>();
		Seq_Attack->AddChild<Con_OntheRight>();
		Seq_Attack->AddChild<Con_IsRight>();

		Sequence_Node* Seq_AttackAnim = Seq_Attack->AddChild<Sequence_Node>();
		Seq_AttackAnim->AddChild<Act_PlayAnim_Attack>();
		Seq_AttackAnim->AddChild<Act_PlayAnim_Idle>();

		// 이동 판단 시퀀스
		Selector_Node* Sel_CheckMoveDir = Seq_Move->AddChild<Selector_Node>();
		Sequence_Node* Seq_CheckMoveLeft = Sel_CheckMoveDir->AddChild<Sequence_Node>();
		Sequence_Node* Seq_CheckMoveRight = Sel_CheckMoveDir->AddChild<Sequence_Node>();

		// 왼쪽 방향 시퀀스
		Seq_CheckMoveLeft->AddChild<Con_IsLeft>();
		Selector_Node* Sel_TurnLeft_ForMove = Seq_CheckMoveLeft->AddChild<Selector_Node>();
		Seq_CheckMoveLeft->AddChild<Act_PlayAnim_Move>();

		Sequence_Node* Seq_CheckOverArea_Left = Sel_TurnLeft_ForMove->AddChild<Sequence_Node>();
		Sel_TurnLeft_ForMove->AddChild<Act_MoveLeft>();

		Seq_CheckOverArea_Left->AddChild<Con_IsOver_LeftArea>();
		Seq_CheckOverArea_Left->AddChild<Act_TurnRight>();
		Seq_CheckOverArea_Left->AddChild<Act_MoveRight>();


		// 오른쪽 방향 시퀀스
		Seq_CheckMoveRight->AddChild<Con_IsRight>();
		Selector_Node* Sel_TurnRight_ForMove = Seq_CheckMoveRight->AddChild<Selector_Node>();
		Seq_CheckMoveRight->AddChild<Act_PlayAnim_Move>();

		Sequence_Node* Seq_CheckOverArea_Right = Sel_TurnRight_ForMove->AddChild<Sequence_Node>();
		Sel_TurnRight_ForMove->AddChild<Act_MoveRight>();

		Seq_CheckOverArea_Right->AddChild<Con_IsOver_RightArea>();
		Seq_CheckOverArea_Right->AddChild<Act_TurnLeft>();
		Seq_CheckOverArea_Right->AddChild<Act_MoveLeft>();
	}

	void Script_Archer::Dead()
	{
	}
}