#include "sszScript_Knight.h"
#include "sszChamp_Knight.h"

#include "CommonObjHeader.h"

// Test
#include "sszTestBT.cpp"

namespace ssz
{
	Script_Knight::Script_Knight()
		: mRoot(nullptr)
	{
	}

	Script_Knight::~Script_Knight()
	{
		delete mRoot;
	}

	void Script_Knight::Initialize()
	{
		std::shared_ptr<AIBB> KnightAIBB = std::make_shared<AIBB>();

		KnightAIBB->AddData<std::wstring>(CHAMPKEY, &GetName());

		KnightAIBB->AddData<GameObject>(GetName(), GetOwner());

		GameObject* pCsr = SceneManager::GetActiveScene()->GetLayer(eLayerType::Cursor).GetGameObjects().front();
		KnightAIBB->AddData<GameObject>(L"Cursor", pCsr);
		
		int* CenterPos = KnightAIBB->CreateData<int>(L"CenterPos");
		*CenterPos = 100;

		// Set BT
		mRoot = new Root_Node(KnightAIBB);

		Selector_Node* KnightBT = mRoot->AddChild<Selector_Node>(); // 최상위 셀렉터 노드


		Sequence_Node* Seq_Dead = KnightBT->AddChild<Sequence_Node>(); // 사망 판단 시퀀스
		Sequence_Node* Seq_Stop = KnightBT->AddChild<Sequence_Node>(); // 정지 판단 시퀀스
		Sequence_Node* Seq_Attack = KnightBT->AddChild<Sequence_Node>(); // 공격 판단 시퀀스
		Sequence_Node* Seq_Move = KnightBT->AddChild<Sequence_Node>(); // 이동 판단 시퀀스

		// 사망 판단 시퀀스
		Seq_Dead->AddChild<Con_CollisionCsr>(); // 정지 버튼 입력 판단
		Seq_Dead->AddChild<Act_PlayAnim_Dead>(); // Idle Animation 재생

		// 정지 판단 시퀀스
		Seq_Stop->AddChild<Con_IsStopBtnPush>(); // 정지 버튼 입력 판단
		Seq_Stop->AddChild<Act_PlayAnim_Idle>(); // Idle Animation 재생


		// 공격 판단 시퀀스
		Seq_Attack->AddChild<Con_CollisionOtehrChamp>();
		Seq_Attack->AddChild<Act_PlayAnim_Attack>();
		Succeeder_Node* Dec_CheckAttackDir_Success = Seq_Attack->AddChild<Succeeder_Node>();
		Selector_Node* Sel_CheckAttackDir = Dec_CheckAttackDir_Success->AddChild<Selector_Node>();

		Sequence_Node* Seq_AttackLeft = Sel_CheckAttackDir->AddChild<Sequence_Node>();
		Sequence_Node* Seq_AttackRight = Sel_CheckAttackDir->AddChild<Sequence_Node>();

		Seq_AttackLeft->AddChild<Con_OntheLeft>();
		Seq_AttackLeft->AddChild<Con_IsRight>();
		Seq_AttackLeft->AddChild<Act_TurnLeft>();

		Seq_AttackRight->AddChild<Con_OntheRight>();
		Seq_AttackRight->AddChild<Con_IsLeft>();
		Seq_AttackRight->AddChild<Act_TurnRight>();

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

	void Script_Knight::Update()
	{
		mRoot->Run();
	}

}