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

	eNodeStatus Root_Node::Run()
	{
		if (mChild == nullptr)
		{
			return NS_INVALID;
		}

		return mChild->Run();
	}

	Decorate_Node::~Decorate_Node()
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
	
	eNodeStatus RdSelector_Node::Run()
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		vector<BT*> vecNode;

		for (BT* child : GetChilds())
			vecNode.push_back(child);

		std::shuffle(vecNode.begin(), vecNode.end(), gen);

		for (BT* child : vecNode)
		{
			if (child->Run() == NS_SUCCESS)
			{
				return NS_SUCCESS;
			}
		}

		return NS_FAILURE;
	}
}