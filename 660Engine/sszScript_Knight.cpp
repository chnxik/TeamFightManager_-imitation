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

		anim->Create(L"knight_idle", L"knight_sprite", Vector2(0.f, 0.f), FrmSize, 5, Vector2(0.f, 0.f), 6.f);
		anim->Create(L"knight_move", L"knight_sprite", Vector2(0.f, FrmSize.y * 1), FrmSize, 8, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_attack", L"knight_sprite", Vector2(0.f, FrmSize.y * 2), FrmSize, 7, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_dead", L"knight_sprite", Vector2(0.f, FrmSize.y * 3), FrmSize, 9, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_skill1", L"knight_sprite", Vector2(0.f, FrmSize.y * 4), FrmSize, 7, Vector2(0.f, 0.f), 8.f);
		anim->Create(L"knight_skill2", L"knight_sprite", Vector2(0.f, FrmSize.y * 5), FrmSize, 7, Vector2(0.f, 0.f), 8.f);

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
		AtkColTr->SetParent(Owner->GetComponent<Transform>()); // �θ� ����ٴϴ� ColObj
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
		// Sequence_Node* Seq_Active_Skill = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-2 ��ų

		Sequence_Node* Seq_Active_Attack = Sel_SelectActive->AddChild<Sequence_Node>(); // 2-2-2-3 �⺻����
		Seq_Active_Attack->AddChild<Con_CheckRagne_Attack>();	// 2-2-2-3-1 �⺻���� ��Ÿ� �Ǵ�
		Seq_Active_Attack->AddChild<Act_SetDir_Target>(); // 2-2-2-3-2 Ÿ�ٹ������� ������ȯ

		Sequence_Node* Seq_AttackAnim = Seq_Active_Attack->AddChild<Sequence_Node>(); // 2-2-2-3-3 ���� �ִϸ��̼�
		Seq_AttackAnim->AddChild<Act_PlayAnim_Attack>();	// 2-2-2-3-3-1 ���� �ִϸ��̼� �ݺ����
		Seq_AttackAnim->AddChild<Act_PlayAnim_Idle>();		// 2-2-2-3-3-2 ���ݾִϸ��̼� ����� Idle�� �ʱ�ȭ

		// [2-3] �̵� �Ǵ� ������
		Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>();
		Selector_Node* Sel_MovePoint = Seq_Move->AddChild<Selector_Node>(); // 2-3-1 �̵����� ���� �Ǵ�
		Sel_MovePoint->AddChild<Con_IsArrive>();			// 2-3-1-1 ��ǥ���� ���� �Ǵ�
		Sel_MovePoint->AddChild<Act_SetMovePoint_Random>();	// 2-3-1-2 ���� �̵� ����

		Seq_Move->AddChild<Act_SetDir_MovePoint>();		// 2-3-2-1 �̵��������� ������ȯ
		Seq_Move->AddChild<Act_Move_Default>();			// 2-3-2-2 �̵��������� �̵�
		Seq_Move->AddChild<Act_PlayAnim_Move>();		// 2-3-2-3 �̵��ִϸ��̼� ���

#pragma region Test BT 1
		/*
		{

			int* CenterPos = BB->CreateData<int>(L"CenterPos");
			*CenterPos = 100;

			// Set BT
			Selector_Node* ChampBT = CreateRootNode(BB)->AddChild<Selector_Node>(); // �ֻ��� ������ ���

			Sequence_Node* Seq_Dead = ChampBT->AddChild<Sequence_Node>(); // ��� �Ǵ� ������
			Sequence_Node* Seq_Stop = ChampBT->AddChild<Sequence_Node>(); // ���� �Ǵ� ������
			Sequence_Node* Seq_Attack = ChampBT->AddChild<Sequence_Node>(); // ���� �Ǵ� ������
			Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>(); // �̵� �Ǵ� ������

			// ��� �Ǵ� ������
			//Seq_Dead->AddChild<Con_CollisionCsr>(); // ���� ��ư �Է� �Ǵ�
			Seq_Dead->AddChild<Con_IsAlive>();
			//Seq_Dead->AddChild<Act_PlayAnim_Dead>(); // Idle Animation ���

			// ���� �Ǵ� ������
			Seq_Stop->AddChild<Con_IsStopBtnPush>(); // ���� ��ư �Է� �Ǵ�
			Seq_Stop->AddChild<Act_PlayAnim_Idle>(); // Idle Animation ���


			// ���� �Ǵ� ������
			Seq_Attack->AddChild<Con_CollisionOtehrChamp>();
			Succeeder_Node* Dec_CheckAttackDir_Success = Seq_Attack->AddChild<Succeeder_Node>();
			Selector_Node* Sel_CheckAttackDir = Dec_CheckAttackDir_Success->AddChild<Selector_Node>();

			Sequence_Node* Seq_AttackLeft = Sel_CheckAttackDir->AddChild<Sequence_Node>();
			Sequence_Node* Seq_AttackRight = Sel_CheckAttackDir->AddChild<Sequence_Node>();


			Seq_AttackLeft->AddChild<Con_OntheLeft>();
			Seq_AttackLeft->AddChild<Con_IsRight>();
			Seq_AttackLeft->AddChild<Act_TurnLeft>();
			Seq_AttackLeft->AddChild<Act_PlayAnim_Attack>();
			Seq_AttackLeft->AddChild<Act_PlayAnim_Idle>();

			Seq_AttackRight->AddChild<Con_OntheRight>();
			Seq_AttackRight->AddChild<Con_IsLeft>();
			Seq_AttackRight->AddChild<Act_TurnRight>();
			Seq_AttackRight->AddChild<Act_PlayAnim_Attack>();
			Seq_AttackLeft->AddChild<Act_PlayAnim_Idle>();

			// �̵� �Ǵ� ������
			Selector_Node* Sel_CheckMoveDir = Seq_Move->AddChild<Selector_Node>();
			Sequence_Node* Seq_CheckMoveLeft = Sel_CheckMoveDir->AddChild<Sequence_Node>();
			Sequence_Node* Seq_CheckMoveRight = Sel_CheckMoveDir->AddChild<Sequence_Node>();

			// ���� ���� ������
			Seq_CheckMoveLeft->AddChild<Con_IsLeft>();
			Selector_Node* Sel_TurnLeft_ForMove = Seq_CheckMoveLeft->AddChild<Selector_Node>();
			Seq_CheckMoveLeft->AddChild<Act_PlayAnim_Move>();

			Sequence_Node* Seq_CheckOverArea_Left = Sel_TurnLeft_ForMove->AddChild<Sequence_Node>();
			Sel_TurnLeft_ForMove->AddChild<Act_MoveLeft>();

			Seq_CheckOverArea_Left->AddChild<Con_IsOver_LeftArea>();
			Seq_CheckOverArea_Left->AddChild<Act_TurnRight>();
			Seq_CheckOverArea_Left->AddChild<Act_MoveRight>();


			// ������ ���� ������
			Seq_CheckMoveRight->AddChild<Con_IsRight>();
			Selector_Node* Sel_TurnRight_ForMove = Seq_CheckMoveRight->AddChild<Selector_Node>();
			Seq_CheckMoveRight->AddChild<Act_PlayAnim_Move>();

			Sequence_Node* Seq_CheckOverArea_Right = Sel_TurnRight_ForMove->AddChild<Sequence_Node>();
			Sel_TurnRight_ForMove->AddChild<Act_MoveRight>();

			Seq_CheckOverArea_Right->AddChild<Con_IsOver_RightArea>();
			Seq_CheckOverArea_Right->AddChild<Act_TurnLeft>();
			Seq_CheckOverArea_Right->AddChild<Act_MoveLeft>();
		}
		*/
#pragma endregion
	}

	void Script_Knight::Dead()
	{
	}

}