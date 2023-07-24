#include "sszBT.h"
#include "sszAIBB.h"

namespace ssz::AI
{
	BT::~BT()
	{
	}


	Decoreate_Node::~Decoreate_Node()
	{
		if (mChild)
		{
			delete mChild;
			mChild = nullptr;
		}
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
				return NS_SUCCESS;
			}
		}

		return NS_FAILURE;
	}
	
	eNodeStatus Sequence_Node::Run()
	{
		for (BT* child : GetChilds())
		{
			if (child->Run() == NS_FAILURE)
			{
				return NS_FAILURE;
			}
		}
		
		return NS_SUCCESS;
	}
	
	eNodeStatus Root_Node::Run()
	{
		if (mChild == nullptr)
		{
			return NS_INVALID;
		}
		
		return mChild->Run();
	}
}