#include "sszScript_Archer.h"
#include "sszChamp_Archer.h"

#include "CommonObjHeader.h"

// Test
#include "sszTestBT.cpp"

namespace ssz
{
	Script_Archer::Script_Archer()
		: mRoot(nullptr)
	{
	}

	Script_Archer::~Script_Archer()
	{
		delete mRoot;
	}

	void Script_Archer::Initialize()
	{
	

		std::shared_ptr<AIBB> ArcherAIBB = std::make_shared<AIBB>();

		ArcherAIBB->AddData<std::wstring>(CHAMPKEY, &GetName());

		ArcherAIBB->AddData<GameObject>(GetName(), GetOwner());

		GameObject* pCsr = SceneManager::GetActiveScene()->GetLayer(eLayerType::Cursor).GetGameObjects().front();
		ArcherAIBB->AddData<GameObject>(L"Cursor", pCsr);

		int* CenterPos = ArcherAIBB->CreateData<int>(L"CenterPos");
		*CenterPos = -100;

		// Set BT
		mRoot = new Root_Node(ArcherAIBB);
		
		Selector_Node* ArcherBT = mRoot->AddChild<Selector_Node>(); // �ֻ��� ������ ���


		Sequence_Node* Seq_Dead = ArcherBT->AddChild<Sequence_Node>(); // ��� �Ǵ� ������
		Sequence_Node* Seq_Stop = ArcherBT->AddChild<Sequence_Node>(); // ���� �Ǵ� ������
		Selector_Node* Sel_AttackOrBack = ArcherBT->AddChild<Selector_Node>(); // ���� �Ǵ� ������
		Sequence_Node* Seq_Move = ArcherBT->AddChild<Sequence_Node>(); // �̵� �Ǵ� ������

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

	void Script_Archer::Update()
	{
		mRoot->Run();
	}
	
}