#include "sszBT.h"
#include "sszAIBB.h"

namespace ssz::AI
{
	BT::~BT()
	{
	}

	Root_Node::Root_Node(std::shared_ptr<AIBB> pAIBB)
		: mChild(nullptr), mCurRunningNode(nullptr)
	{
		SetAIBB(pAIBB);
		mAIBB->RegistRunningNode(&mCurRunningNode);
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
		if (mCurRunningNode != nullptr)
		{
			if (mCurRunningNode->Run() == NS_RUNNING)
				return NS_RUNNING;

			mCurRunningNode = nullptr;
			
			return NS_SUCCESS;
		}
		else if (mChild != nullptr)
			return mChild->Run();

		return NS_INVALID;
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
			eNodeStatus eStatus = child->Run();
			
			if (eStatus == NS_SUCCESS)
				return NS_SUCCESS;
			
			if (eStatus == NS_RUNNING)
			{
				mAIBB->SetRunningNode(child);
				return NS_RUNNING;
			}
		}

		return NS_FAILURE;
	}
	
	eNodeStatus Sequence_Node::Run()
	{
		for (BT* child : GetChilds())
		{
			eNodeStatus eStatus = child->Run();

			if (eStatus == NS_FAILURE)
				return NS_FAILURE;

			if (eStatus == NS_RUNNING)
			{
				mAIBB->SetRunningNode(child);
				return NS_RUNNING;
			}
		}
		
		return NS_SUCCESS;
	}
	
	eNodeStatus RandSelector_Node::Run()
	{
		std::random_device rd;
		std::mt19937 gen(rd());

		vector<BT*> vecNode;

		for (BT* child : GetChilds())
			vecNode.emplace_back(child);

		std::shuffle(vecNode.begin(), vecNode.end(), gen);

		for (BT* child : vecNode)
		{
			eNodeStatus eStatus = child->Run();

			if (eStatus == NS_SUCCESS)
				return NS_SUCCESS;

			if (eStatus == NS_RUNNING)
			{
				mAIBB->SetRunningNode(child);
				return NS_RUNNING;
			}
		}

		return NS_FAILURE;
	}
}