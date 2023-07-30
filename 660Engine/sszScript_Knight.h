#pragma once
#include "sszScript.h"
#include "CommonObjHeader.h"

namespace ssz
{
	class Script_Knight : public Script
	{
	public:
		Script_Knight();
		virtual ~Script_Knight();

		virtual void Initialize() override;
		virtual void Update() override;

	private:
		Root_Node* mRoot;
	};
}