#include "sszBehaviorTree.h"

namespace ssz
{
	CompositeNode::CompositeNode()
	{
	}
	
	CompositeNode::~CompositeNode()
	{
		for (BT* child : getChild())
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