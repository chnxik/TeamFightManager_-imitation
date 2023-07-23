#pragma once
#include <sszScript.h>

namespace ssz
{
	class Transform;
	class Animator;

	class TestScript : public Script
	{
	public:
		struct Testst
		{
			int a;
		};

		TestScript();
		virtual ~TestScript();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		AI::Sequence* root;
		Transform* tr;
		Animator* anim;
	};
}