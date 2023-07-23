#include "sszBehaviorTree.h"

namespace ssz::AI
{
	BT::BT()
	{
	}

	BT::~BT()
	{
		for (BT* child : mChild)
		{
			delete child;
			child = nullptr;
		}
	}

	bool Selector::Run()
	{
		for (BT* child : getChild())
		{
			if (child->Run())
			{
				return true;
			}
		}
		return false;
	}
	
	bool Sequence::Run()
	{
		for (BT* child : getChild())
		{
			if (!child->Run())
			{
				return false;
			}
		}
		return true;
	}
}