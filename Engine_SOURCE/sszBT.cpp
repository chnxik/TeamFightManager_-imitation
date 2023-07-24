#include "sszBT.h"
#include "sszAIBB.h"

namespace ssz::AI
{
	BT::~BT()
	{
	}

	Root::~Root()
	{
		if (mChild)
		{
			delete mChild;
			mChild = nullptr;
		}
	}

	CompositeNode::~CompositeNode()
	{
		for (BT* child : mChilds)
		{
			delete child;
			child = nullptr;
		}
	}

	eNodeStatus Selector::Run()
	{
		for (BT* child : GetChilds())
		{
			if (child->Run() == NS_SUCCESS)
			{
				return SetStatus(NS_SUCCESS);
			}
			else if (child->Run() == NS_RUNNING)
			{
				return SetStatus(NS_RUNNING);
			}
		}

		return SetStatus(NS_FAILURE);
	}
	
	eNodeStatus Sequence::Run()
	{
		for (BT* child : GetChilds())
		{
			if (child->Run() == NS_FAILURE)
			{
				return SetStatus(NS_FAILURE);
			}
			else if (child->Run() == NS_RUNNING)
			{
				return SetStatus(NS_RUNNING);;
			}
		}
		
		return SetStatus(NS_FAILURE);
	}
	
	eNodeStatus Root::Run()
	{
		if (mChild == nullptr)
		{
			return SetStatus(NS_INVALID);
		}
		
		return mChild->Run();
	}
	
}