#include "sszBT.h"
#include "sszAIBB.h"

namespace ssz::AI
{
	BT::~BT()
	{
	}

	Root_Node::~Root_Node()
	{
		if (mChild)
		{
			delete mChild;
			mChild = nullptr;
		}
	}

	Composite_Node::~Composite_Node()
	{
		for (BT* child : mChilds)
		{
			delete child;
			child = nullptr;
		}
	}

	eNodeStatus Selector_Node::Run()
	{
		for (BT* child : GetChilds())
		{
			if (child->Run() == NS_SUCCESS)
			{
				return SetStatus(NS_SUCCESS);
			}
		}

		return SetStatus(NS_FAILURE);
	}
	
	eNodeStatus Sequence_Node::Run()
	{
		for (BT* child : GetChilds())
		{
			if (child->Run() == NS_FAILURE)
			{
				return SetStatus(NS_FAILURE);
			}
		}
		
		return SetStatus(NS_SUCCESS);
	}
	
	eNodeStatus Root_Node::Run()
	{
		if (mChild == nullptr)
		{
			return SetStatus(NS_INVALID);
		}
		
		return mChild->Run();
	}
	
}