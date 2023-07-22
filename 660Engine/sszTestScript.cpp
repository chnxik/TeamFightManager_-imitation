#include "sszTestScript.h"
#include "CommonObjHeader.h"

#include "sszGameObject.h"

#include "sszInput.h"
#include "sszTime.h"

// Component
#include "sszTransform.h"
#include "sszAnimator.h"

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

			anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), Vector2(64.f, 64.f), 4, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_move", L"archer_sprite", Vector2(0.f, 64.f), Vector2(64.f, 64.f), 8, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_attack", L"archer_sprite", Vector2(0.f, 128.f), Vector2(64.f, 64.f), 8, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_dead", L"archer_sprite", Vector2(0.f, 192.f), Vector2(64.f, 64.f), 8, Vector2(0.f, 0.f), 7.f);
			anim->Create(L"archer_skill", L"archer_sprite", Vector2(0.f, 256.f), Vector2(64.f, 64.f), 8, Vector2(0.f, 0.f), 7.f);
			anim->PlayAnimation(L"archer_idle", true);
		}

		// Behavior Tree Setting
		{
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
		/*
		Vector3 Pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::LEFT))
		{
			if (!(tr->IsLeft()))
				tr->SetLeft();

			// Pos.x -= 100.f * (float)Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			if (!(tr->IsRight()))
				tr->SetRight();

			// Pos.x += 100.f * (float)Time::DeltaTime();
		}

		tr->SetPosition(Pos);
		*/

		while (!root->Run())
		{
		}
	}

	

}
