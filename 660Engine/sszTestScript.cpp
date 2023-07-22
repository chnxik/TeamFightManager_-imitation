#include "sszTestScript.h"
#include "CommonObjHeader.h"

#include "sszGameObject.h"

#include "sszInput.h"
#include "sszTime.h"

// Component
#include "sszTransform.h"
#include "sszAnimator.h"

namespace ssz
{
	TestScript::TestScript()
		: tr(nullptr)
		, anim(nullptr)
	{
	}

	TestScript::~TestScript()
	{
	}

	void TestScript::Initialize()
	{
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(L"archer_sprite", L"..\\Resources\\useResource\\ChampSprite\\archer\\archer_sprite\\archer.png");
		LoadMaterial(L"archer_spriteMt", L"AnimationShader", L"archer_sprite", eRenderingMode::Transparent);

		// Owner 의 Transform에 접근해 초기 Pos와 Scale을 가져온다.
		tr = GetOwner()->GetComponent<Transform>();
		anim = GetOwner()->GetComponent<Animator>();

		anim->Create(L"archer_idle", L"archer_sprite", Vector2(0.f, 0.f), Vector2(64.f, 64.f), 4, Vector2(0.f, 0.f), 7.f);
		anim->PlayAnimation(L"archer_idle", true);
	}

	void TestScript::Update()
	{
		Vector3 Pos = tr->GetPosition();

		if (Input::GetKey(eKeyCode::LEFT))
		{
			if (!(tr->IsLeft()))
				tr->SetLeft();

			Pos.x -= 100.f * (float)Time::DeltaTime();
		}
		else if (Input::GetKey(eKeyCode::RIGHT))
		{
			if (!(tr->IsRight()))
				tr->SetRight();

			Pos.x += 100.f * (float)Time::DeltaTime();
		}

		tr->SetPosition(Pos);
	}
	void TestScript::Complete()
	{
	}
}
