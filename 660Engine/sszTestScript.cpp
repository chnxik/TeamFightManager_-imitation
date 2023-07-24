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

			anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), Vector2(64.f, 64.f), 4, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_move", L"archer_sprite", Vector2(0.f, 64.f), Vector2(64.f, 64.f), 8, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_attack", L"archer_sprite", Vector2(0.f, 128.f), Vector2(64.f, 64.f), 7, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_dead", L"archer_sprite", Vector2(0.f, 192.f), Vector2(64.f, 64.f), 9, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_skill", L"archer_sprite", Vector2(0.f, 256.f), Vector2(64.f, 64.f), 17, Vector2(0.f, 0.f), 7.f);
			anim->PlayAnimation(L"archer_idle", true);
		}

		// Behavior Tree Setting
		{
			// Set AIBB
			std::shared_ptr<AIBB> TestAIBB = std::make_shared<AIBB>();
			TestAIBB->CreateData<int>(L"TestInt");
			TestAIBB->AddData<GameObject>(L"Champ_archer", GetOwner());

			GameObject* pCursor = SceneManager::GetActiveScene()->GetLayer(eLayerType::Cursor).GetGameObjects().front();
			TestAIBB->AddData<GameObject>(L"Cursor", pCursor);

			// Set BT
			root = new Root(TestAIBB);

			Selector* BS = new Selector;
			Sequence* seqStop = new Sequence;
			Sequence* seqAttack = new Sequence;
			Sequence* seqMove = new Sequence;

			CheckStop* stopcheck = new CheckStop(TestAIBB);
			PlayIdleAnim* PlayIdle = new PlayIdleAnim(TestAIBB);

			DetectedCursor100* DetectCsr = new DetectedCursor100(TestAIBB);
			Selector* CheckAttackDir = new Selector;

			Sequence* seqAttackLeft = new Sequence;
			Sequence* seqAttackRight = new Sequence;

			CheckCsrifLeft* CheckCsrLeft = new CheckCsrifLeft(TestAIBB);
			CheckCsrifRight* CheckCsrRight = new CheckCsrifRight(TestAIBB);

			CheckLeft* IsAttackLeft = new CheckLeft(TestAIBB);
			CheckRight* IsAttackRight = new CheckRight(TestAIBB);

			TurnLeft* ActTurnLeft = new TurnLeft(TestAIBB);
			TurnRight* ActTurnRight = new TurnRight(TestAIBB);

			PlayAttackAnim* AttackMotion = new PlayAttackAnim(TestAIBB);
			PlayMoveAnim* MoveMotion = new PlayMoveAnim(TestAIBB);

			Selector* CheckMoveDir = new Selector;
			Sequence* seqMoveLeft = new Sequence;
			Sequence* seqMoveRight = new Sequence;

			CheckLeft* IsMoveLeft = new CheckLeft(TestAIBB);
			CheckRight* IsMoveRight = new CheckRight(TestAIBB);

			Selector* Sel_MoveLeftDir = new Selector;
			Selector* Sel_MoveRightDir = new Selector;

			Sequence* seqCheckLeftArea = new Sequence;
			Sequence* seqCheckRightArea = new Sequence;

			CheckLeftDist* seqCheckLeftDist = new CheckLeftDist(TestAIBB);
			CheckRightDist* seqCheckRightDist = new CheckRightDist(TestAIBB);

			MoveLeft* ActMoveLeft = new MoveLeft(TestAIBB);
			MoveRight* ActMoveRight = new MoveRight(TestAIBB);

			root->AddChild(BS);

			BS->AddChild(seqStop);
			BS->AddChild(seqAttack);
			BS->AddChild(seqMove);

			seqStop->AddChild(stopcheck);
			seqStop->AddChild(PlayIdle);

			seqAttack->AddChild(DetectCsr);
			seqAttack->AddChild(CheckAttackDir);
			seqAttack->AddChild(AttackMotion);

			CheckAttackDir->AddChild(seqAttackLeft);
			CheckAttackDir->AddChild(seqAttackRight);
			
			seqAttackLeft->AddChild(CheckCsrLeft);
			seqAttackLeft->AddChild(IsAttackLeft);
			seqAttackLeft->AddChild(ActTurnLeft);

			seqAttackRight->AddChild(CheckCsrRight);
			seqAttackRight->AddChild(IsAttackRight);
			seqAttackRight->AddChild(ActTurnRight);

			seqMove->AddChild(CheckMoveDir);
			CheckMoveDir->AddChild(seqMoveLeft);
			CheckMoveDir->AddChild(seqMoveRight);

			seqMoveLeft->AddChild(IsMoveLeft);
			seqMoveLeft->AddChild(seqCheckLeftArea);

			seqCheckLeftArea->AddChild(seqCheckLeftDist);
			seqCheckLeftArea->AddChild(ActTurnRight);
			seqCheckLeftArea->AddChild(ActMoveRight);
			seqCheckLeftArea->AddChild(MoveMotion);

			seqMoveLeft->AddChild(ActMoveLeft);
			seqMoveLeft->AddChild(MoveMotion);

			seqMoveRight->AddChild(IsMoveRight);
			seqMoveRight->AddChild(seqCheckRightArea);

			seqCheckRightArea->AddChild(seqCheckRightDist);
			seqCheckRightArea->AddChild(ActTurnLeft);
			seqCheckRightArea->AddChild(ActMoveLeft);
			seqCheckRightArea->AddChild(MoveMotion);

			seqMoveRight->AddChild(ActMoveRight);
			seqMoveRight->AddChild(MoveMotion);
		}
	}

	void TestScript::Update()
	{
		while (root->Run() == NS_FAILURE)
		{
		}
	}
}
