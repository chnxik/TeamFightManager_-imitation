#pragma once
#include "sszScript.h"
#include "CommonObjHeader.h"

namespace ssz
{
	class Script_Archer : public Script
	{
	public:
		Script_Archer();
		virtual ~Script_Archer();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		Root_Node* mRoot;
	};
}