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
		Owner->SetChampInfo(eChampType::MARKSMAN, 42, 0.67f, 120, 5, 100, 3); // è�Ǿ� ���� �Է�
		Owner->InitIGInfo(0, 0);	// �ΰ��� ���� ����

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
		
		Play_Idle();
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
		AtkColTr->SetParent(Owner->GetComponent<Transform>()); // �θ� ����ٴϴ� ColObj
		Collider2D* AttackArea = ATKCOL->GetComponent<Collider2D>();
		AttackArea->SetType(eColliderType::Circle);

		float Rng = Owner->GetChampInfo().RNG * 2.f;
		ColScale = -Owner->GetComponent<Transform>()->GetScale() + Vector3(Rng, Rng, 1.f);
		AttackArea->SetOffsetSize(ColScale);

		AttackArea->SetOffsetPos(Vector3(0.f, 10.f, 0.f));
	}

	void Script_Archer::InitBT()
	{
		std::shared_ptr<AIBB> ptrAIBB = std::make_shared<AIBB>();

		ptrAIBB->AddData<std::wstring>(CHAMPKEY, &GetName());

		ptrAIBB->AddData<GameObject>(GetName(), GetOwner());

		GameObject* pCsr = TGM::GetCursor();
		ptrAIBB->AddData<GameObject>(L"Cursor", pCsr);

		int* CenterPos = ptrAIBB->CreateData<int>(L"CenterPos");
		*CenterPos = -100;

		// Set BT
		Selector_Node* ChampBT = CreateRootNode(ptrAIBB)->AddChild<Selector_Node>(); // �ֻ��� ������ ���


		Sequence_Node* Seq_Dead = ChampBT->AddChild<Sequence_Node>(); // ��� �Ǵ� ������
		Sequence_Node* Seq_Stop = ChampBT->AddChild<Sequence_Node>(); // ���� �Ǵ� ������
		Selector_Node* Sel_AttackOrBack = ChampBT->AddChild<Selector_Node>(); // ���� �Ǵ� ������
		Sequence_Node* Seq_Move = ChampBT->AddChild<Sequence_Node>(); // �̵� �Ǵ� ������

		// ��� �Ǵ� ������
		Seq_Dead->AddChild<Con_CollisionCsr>(); // Csr �浹 �Ǵ�
		Seq_Dead->AddChild<Act_PlayAnim_Dead>(); // Idle Animation ���

		// ���� �Ǵ� ������
		Seq_Stop->AddChild<Con_IsStopBtnPush>(); // ���� ��ư �Է� �Ǵ�
		Seq_Stop->AddChild<Act_PlayAnim_Idle>(); // Idle Animation ���


		// ���� �Ǵ� ������
		Sequence_Node* Seq_Attack = Sel_AttackOrBack->AddChild<Sequence_Node>();

		Seq_Attack->AddChild<Con_CollisionOtehrChamp>();
		Seq_Attack->AddChild<Con_MustBack>();
		Seq_Attack->AddChild<Con_OntheRight>();
		Seq_Attack->AddChild<Con_IsRight>();
		Seq_Attack->AddChild<Act_PlayAnim_Attack>();

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

	void Script_Archer::Dead()
	{
	}
	
	void Script_Archer::Play_Idle()
	{
		GetOwner()->GetComponent<Animator>()->PlayAnimation(L"archer_idle", true);
	}
	
	void Script_Archer::Play_Move()
	{
		GetOwner()->GetComponent<Animator>()->PlayAnimation(L"archer_move", true);
	}
	
	void Script_Archer::Play_Attack()
	{
		GetOwner()->GetComponent<Animator>()->PlayAnimation(L"archer_attack", false);
	}
	
	void Script_Archer::Play_Dead()
	{
		GetOwner()->GetComponent<Animator>()->PlayAnimation(L"archer_dead", false);
	}
	
	void Script_Archer::Play_Skill1()
	{
		GetOwner()->GetComponent<Animator>()->PlayAnimation(L"archer_skill", true);
	}
	
	void Script_Archer::Play_Skill2()
	{
	}
}