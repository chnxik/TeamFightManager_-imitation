#pragma once
#include "sszEngine.h"

#define NS_SUCCESS ssz::AI::eNodeStatus::SUCCESS
#define NS_FAILURE ssz::AI::eNodeStatus::FAILURE
#define NS_RUNNING ssz::AI::eNodeStatus::RUNNING
#define NS_INVALID ssz::AI::eNodeStatus::INVALID

#define FINDBBDATA(T,key) ssz::AI::BT::mAIBB->FindData<T>(key);

namespace ssz::AI
{
	class AIBB;
	using namespace std;

	enum class eNodeStatus
	{
		SUCCESS,	// 성공
		FAILURE,	// 실패
		RUNNING,	// 진행중
		INVALID		// 유효하지 않음
	};

	// ============================ 베이스 ==============================

	class BT // Base 노드
	{
	public:
		BT() : mAIBB(nullptr) {}
		virtual ~BT();

		virtual eNodeStatus Run() = 0;

		void SetAIBB(std::shared_ptr<AIBB> pAIBB) { mAIBB = pAIBB; }
		std::shared_ptr<AIBB> GetAIBB() { return mAIBB; }

	protected:
		std::shared_ptr<AIBB> mAIBB;
	};

	// ============================ Root Node ==============================

	class Root_Node : public BT // 뿌리 노드
	{
	public:
		Root_Node(std::shared_ptr<AIBB> pAIBB);
		virtual ~Root_Node();

		BT* GetChild() { return mChild; }

		template<typename T>
		T* AddChild()
		{
			T* NewNode = new T();

			mChild = dynamic_cast<BT*>(NewNode);

			if (mChild == nullptr)
				return nullptr;

			mChild->SetAIBB(mAIBB);

			return NewNode;
		}

		virtual eNodeStatus Run();
		virtual void Clear();

	private:
		BT* mChild;
		BT* mCurRunningNode;
	};

	// ============================ Decorate Node =========================
	class Decorate_Node : public BT
	{
	public:
		Decorate_Node() : mChild(nullptr) {}
		virtual ~Decorate_Node();

		BT* GetChild() { return mChild; }

		template<typename T>
		T* AddChild()
		{
			T* NewNode = new T();

			mChild = dynamic_cast<BT*>(NewNode);

			if (mChild == nullptr)
				return nullptr;

			mChild->SetAIBB(mAIBB);

			return NewNode;
		}

		virtual eNodeStatus Run() = 0;

	private :
		BT* mChild;
	};

	// 반드시 성공을 반환
	class Succeeder_Node : public Decorate_Node
	{
	public:
		virtual eNodeStatus Run()
		{
			GetChild()->Run();

			return NS_SUCCESS;
		}
	};

	// 성공을 반환할 때 까지 반복
	class Repeat_Until_Node : public Decorate_Node
	{
	public:
		virtual eNodeStatus Run()
		{
			while (GetChild()->Run() != NS_SUCCESS) {}
		}
	};

	// ========================================== Composite Node =================================

	class Composite_Node : public BT // 복합노드
	{
	public:
		virtual ~Composite_Node();

		list<BT*> GetChilds() { return mChilds; }
		// void AddChild(BT* child) { mChilds.emplace_back(child); }

		template <typename T>
		T* AddChild()
		{
			T* NewNode = new T();

			BT* childNode = dynamic_cast<BT*>(NewNode);

			if (childNode == nullptr)
				return nullptr;

			childNode->SetAIBB(mAIBB);

			mChilds.emplace_back(childNode);

			return NewNode;
		}

	private:
		list<BT*> mChilds;
	};

	class Selector_Node : public Composite_Node // OR 개념 노드
	{
	public:
		virtual eNodeStatus Run() override;
	};

	class Sequence_Node : public Composite_Node // AND 개념 노드
	{
	public:
		virtual eNodeStatus Run() override;
	};
		
	class RandSelector_Node : public Composite_Node // 매 실행마다 자식노드의 순서를 셔플 (무작위)
	{
	public:
		virtual eNodeStatus Run() override;
	};

	// =========================================== Leaf Node ======================================

	// ============================= Condition Node ===================================
	class Condition_Node : public BT // 컨디션 판단 노드
	{
	public:
		virtual eNodeStatus Run() = 0;
	};


	// ============================= Action Node =====================================
	class Action_Node : public BT	// 행동 실행 노드
	{
	public:
		virtual eNodeStatus Run() = 0;
	};
}