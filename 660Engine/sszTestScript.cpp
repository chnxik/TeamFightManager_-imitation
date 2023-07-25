#include "sszTestScript.h"
#include "CommonObjHeader.h"

// BT
#include "sszTestBT.cpp"
#include "sszAIBB.h"

namespace ssz
{
	TestScript::TestScript()
		: root(nullptr)
		, tr(nullptr)
		, anim(nullptr)
	{
	}

	TestScript::~TestScript()
	{
		delete root;
	}

	void TestScript::Initialize()
	{
		// Animator, Atals Setting
		{
			std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"archer_sprite", L"..\\Resources\\useResource\\ChampSprite\\archer\\archer_sprite\\archer.png");
			LoadMaterial(L"archer_spriteMt", L"AnimationShader", L"archer_sprite", eRenderingMode::Transparent);

			// Owner 의 Transform에 접근해 초기 Pos와 Scale을 가져온다.
			tr = GetOwner()->GetComponent<Transform>();
			anim = GetOwner()->GetComponent<Animator>();

			anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), Vector2(64.f, 64.f), 4, Vector2(0.f, 0.f), 6.f);
			anim->Create(L"archer_move", L"archer_sprite", Vector2(0.f, 64.f), Vector2(64.f, 64.f), 8, Vector2(0.f, 0.f), 8.f);
			anim->Create(L"archer_attack", L"archer_sprite", Vector2(0.f, 128.f), Vector2(64.f, 64.f), 7, Vector2(0.f, 0.f), 8.f);
			anim->Create(L"archer_dead", L"archer_sprite", Vector2(0.f, 192.f), Vector2(64.f, 64.f), 9, Vector2(0.f, 0.f), 8.f);
			anim->Create(L"archer_skill", L"archer_sprite", Vector2(0.f, 256.f), Vector2(64.f, 64.f), 17, Vector2(0.f, 0.f), 8.f);
			anim->PlayAnimation(L"archer_idle", true);
		}

		// Behavior Tree Setting
		{
			// Set AIBB
			std::shared_ptr<AIBB> TestAIBB = std::make_shared<AIBB>();	// TestBT용 AI BlackBoard 생성
			TestAIBB->AddData<GameObject>(L"Champ_archer", GetOwner()); // 참조 Object 추가
			
			GameObject* pCsr = SceneManager::GetActiveScene()->GetLayer(eLayerType::Cursor).GetGameObjects().front();
			TestAIBB->AddData<GameObject>(L"Cursor", pCsr);

			// Set BT
			root = new Root_Node(TestAIBB);
			
			Selector_Node* ArcherBT = root->AddChild<Selector_Node>(); // 최상위 셀렉터 노드


			Sequence_Node* Seq_Dead = ArcherBT->AddChild<Sequence_Node>(); // 사망 판단 시퀀스
			Sequence_Node* Seq_Stop = ArcherBT->AddChild<Sequence_Node>(); // 정지 판단 시퀀스
			Sequence_Node* Seq_Attack = ArcherBT->AddChild<Sequence_Node>(); // 공격 판단 시퀀스
			Sequence_Node* Seq_Move = ArcherBT->AddChild<Sequence_Node>(); // 이동 판단 시퀀스

			// 사망 판단 시퀀스
			Seq_Dead->AddChild<Con_CollisionCsr>(); // 정지 버튼 입력 판단
			Seq_Dead->AddChild<Act_PlayAnim_Dead>(); // Idle Animation 재생
			
			// 정지 판단 시퀀스
			Seq_Stop->AddChild<Con_IsStopBtnPush>(); // 정지 버튼 입력 판단
			Seq_Stop->AddChild<Act_PlayAnim_Idle>(); // Idle Animation 재생


			// 공격 판단 시퀀스
			Seq_Attack->AddChild<Con_DetectCsr_300px>();
			Seq_Attack->AddChild<Act_PlayAnim_Attack>();
			Succeeder_Node* Dec_CheckAttackDir_Success = Seq_Attack->AddChild<Succeeder_Node>();
			Selector_Node* Sel_CheckAttackDir = Dec_CheckAttackDir_Success->AddChild<Selector_Node>();

			Sequence_Node* Seq_AttackLeft = Sel_CheckAttackDir->AddChild<Sequence_Node>();
			Sequence_Node* Seq_AttackRight = Sel_CheckAttackDir->AddChild<Sequence_Node>();
			
			Seq_AttackLeft->AddChild<Con_CsrOntheLeft>();
			Seq_AttackLeft->AddChild<Con_IsRight>();
			Seq_AttackLeft->AddChild<Act_TurnLeft>();

			Seq_AttackRight->AddChild<Con_CsrOntheRight>();
			Seq_AttackRight->AddChild<Con_IsLeft>();
			Seq_AttackRight->AddChild<Act_TurnRight>();

			// 이동 판단 시퀀스
			Selector_Node* Sel_CheckMoveDir= Seq_Move->AddChild<Selector_Node>();
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
	}

	void TestScript::Update()
	{
		while (root->Run() == NS_FAILURE)
		{
		};
	}
}
