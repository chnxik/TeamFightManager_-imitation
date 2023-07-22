#pragma once
#include <sszScript.h>

namespace ssz
{
	class Transform;
	class Animator;

	class TestScript : public Script
	{
	public:
		TestScript();
		virtual ~TestScript();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		Sequence* root;
		Transform* tr;
		Animator* anim;
	};
}