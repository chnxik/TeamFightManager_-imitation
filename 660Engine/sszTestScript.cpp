#include "sszTestScript.h"
#include "CommonObjHeader.h"

// BT
#include "sszTestBT.cpp"

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
			bool IsSuccess = Blackboard::CreateData<int>(L"Testint");

			int* Testint = Blackboard::FindData<int>(L"Testint");
			*Testint = 158;

			root = new Sequence;
			Selector* Move = new Selector;
			Sequence* LeftMove = new Sequence;
			Sequence* RightMove = new Sequence;
		
			CheckStop* IsStop = new CheckStop(anim);
			CheckLeft* mCheckLeft = new CheckLeft(tr);
			CheckRight* mCheckRight = new CheckRight(tr);
			CheckLeftDist* mCheckLDist = new CheckLeftDist(tr);
			CheckRightDist* mCheckRDist = new CheckRightDist(tr);
		
			root->addChild(Move);
		
			Move->addChild(IsStop);
			Move->addChild(LeftMove);
			Move->addChild(RightMove);
		
			LeftMove->addChild(mCheckLeft);
			LeftMove->addChild(mCheckLDist);
		
			RightMove->addChild(mCheckRight);
			RightMove->addChild(mCheckRDist);
		}
	}

	void TestScript::Update()
	{
		root->Run();
	}
}
