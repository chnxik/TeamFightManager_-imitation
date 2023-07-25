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

			// Owner �� Transform�� ������ �ʱ� Pos�� Scale�� �����´�.
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
			std::shared_ptr<AIBB> TestAIBB = std::make_shared<AIBB>();	// TestBT�� AI BlackBoard ����
			TestAIBB->AddData<GameObject>(L"Champ_archer", GetOwner()); // ���� Object �߰�
			
			root = new Root_Node();

			RdSelector_Node* RandomTest = root->AddChild<RdSelector_Node>();

			RandomTest->AddChild<Node_A>(TestAIBB);
			RandomTest->AddChild<Node_B>(TestAIBB);
			RandomTest->AddChild<Node_C>(TestAIBB);

			/*
			

			GameObject* pCsr = SceneManager::GetActiveScene()->GetLayer(eLayerType::Cursor).GetGameObjects().front();
			TestAIBB->AddData<GameObject>(L"Cursor", pCsr);

			// Set BT
			root = new Root_Node(TestAIBB);
			
			Selector_Node* ArcherBT = root->AddChild<Selector_Node>(); // �ֻ��� ������ ���

			Sequence_Node* Seq_Dead = ArcherBT->AddChild<Sequence_Node>(); // ��� �Ǵ� ������
			Sequence_Node* Seq_Stop = ArcherBT->AddChild<Sequence_Node>(); // ���� �Ǵ� ������
			Sequence_Node* Seq_Attack = ArcherBT->AddChild<Sequence_Node>(); // ���� �Ǵ� ������
			Sequence_Node* Seq_Move = ArcherBT->AddChild<Sequence_Node>(); // �̵� �Ǵ� ������

			// ��� �Ǵ� ������
			Seq_Dead->AddChild<Con_CollisionCsr>(TestAIBB); // ���� ��ư �Է� �Ǵ�
			Seq_Dead->AddChild<Act_PlayAnim_Dead>(TestAIBB); // Idle Animation ���
			
			// ���� �Ǵ� ������
			Seq_Stop->AddChild<Con_IsStopBtnPush>(TestAIBB); // ���� ��ư �Է� �Ǵ�
			Seq_Stop->AddChild<Act_PlayAnim_Idle>(TestAIBB); // Idle Animation ���


			// ���� �Ǵ� ������
			Seq_Attack->AddChild<Con_DetectCsr_300px>(TestAIBB);
			Seq_Attack->AddChild<Act_PlayAnim_Attack>(TestAIBB);
			AllSuccess_Node* Dec_CheckAttackDir_Success = Seq_Attack->AddChild<AllSuccess_Node>();
			Selector_Node* Sel_CheckAttackDir = Dec_CheckAttackDir_Success->AddChild<Selector_Node>();

			Sequence_Node* Seq_AttackLeft = Sel_CheckAttackDir->AddChild<Sequence_Node>();
			Sequence_Node* Seq_AttackRight = Sel_CheckAttackDir->AddChild<Sequence_Node>();
			
			Seq_AttackLeft->AddChild<Con_CsrOntheLeft>(TestAIBB);
			Seq_AttackLeft->AddChild<Con_IsRight>(TestAIBB);
			Seq_AttackLeft->AddChild<Act_TurnLeft>(TestAIBB);

			Seq_AttackRight->AddChild<Con_CsrOntheRight>(TestAIBB);
			Seq_AttackRight->AddChild<Con_IsLeft>(TestAIBB);
			Seq_AttackRight->AddChild<Act_TurnRight>(TestAIBB);

			// �̵� �Ǵ� ������
			Selector_Node* Sel_CheckMoveDir= Seq_Move->AddChild<Selector_Node>();
			Sequence_Node* Seq_CheckMoveLeft = Sel_CheckMoveDir->AddChild<Sequence_Node>();
			Sequence_Node* Seq_CheckMoveRight = Sel_CheckMoveDir->AddChild<Sequence_Node>();

			// ���� ���� ������
			Seq_CheckMoveLeft->AddChild<Con_IsLeft>(TestAIBB);
			Selector_Node* Sel_TurnLeft_ForMove = Seq_CheckMoveLeft->AddChild<Selector_Node>();
			Seq_CheckMoveLeft->AddChild<Act_PlayAnim_Move>(TestAIBB);

			Sequence_Node* Seq_CheckOverArea_Left = Sel_TurnLeft_ForMove->AddChild<Sequence_Node>();
			Sel_TurnLeft_ForMove->AddChild<Act_MoveLeft>(TestAIBB);

			Seq_CheckOverArea_Left->AddChild<Con_IsOver_LeftArea>(TestAIBB);
			Seq_CheckOverArea_Left->AddChild<Act_TurnRight>(TestAIBB);
			Seq_CheckOverArea_Left->AddChild<Act_MoveRight>(TestAIBB);


			// ������ ���� ������
			Seq_CheckMoveRight->AddChild<Con_IsRight>(TestAIBB);
			Selector_Node* Sel_TurnRight_ForMove = Seq_CheckMoveRight->AddChild<Selector_Node>();
			Seq_CheckMoveRight->AddChild<Act_PlayAnim_Move>(TestAIBB);

			Sequence_Node* Seq_CheckOverArea_Right = Sel_TurnRight_ForMove->AddChild<Sequence_Node>();
			Sel_TurnRight_ForMove->AddChild<Act_MoveRight>(TestAIBB);

			Seq_CheckOverArea_Right->AddChild<Con_IsOver_RightArea>(TestAIBB);
			Seq_CheckOverArea_Right->AddChild<Act_TurnLeft>(TestAIBB);
			Seq_CheckOverArea_Right->AddChild<Act_MoveLeft>(TestAIBB);

			*/
		}
	}

	void TestScript::Update()
	{
		while (root->Run() == NS_FAILURE)
		{
		};
	}
}
