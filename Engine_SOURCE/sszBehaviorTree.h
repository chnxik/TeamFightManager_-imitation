#pragma once
#include "sszEngine.h"

#define NS_SUCCESS ssz::AI::eNodeStatus::SUCCESS
#define NS_FAILURE ssz::AI::eNodeStatus::FAILURE
#define NS_RUNNING ssz::AI::eNodeStatus::RUNNING
#define NS_INVALID ssz::AI::eNodeStatus::INVALID

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

	class BT // Base 노드
	{
	public:
		BT() : mNodeStatus(NS_INVALID), mAIBB(nullptr) {}
		BT(std::shared_ptr<AIBB> pAIBB) : mNodeStatus(NS_INVALID), mAIBB(pAIBB) {}
		virtual ~BT();

		virtual eNodeStatus Run() = 0;

		eNodeStatus SetStatus(eNodeStatus eNS) { mNodeStatus = eNS; return mNodeStatus; }
		eNodeStatus GetStatus() { return mNodeStatus; }

	protected:
		eNodeStatus mNodeStatus;
		std::shared_ptr<AIBB> mAIBB;
	};

	class Root : public BT // 뿌리 노드
	{
	public:
		virtual ~Root();

		Root(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB), mChild(nullptr) {}

		const BT* GetChild() const { return mChild; }
		void AddChild(BT* child) { mChild = child; }

		virtual eNodeStatus Run();

	private:
		BT* mChild;
	};

	class CompositeNode : public BT // 복합노드
	{
	public:
		virtual ~CompositeNode();

		const list<BT*>& GetChilds() const { return mChilds; }
		void AddChild(BT* child) { mChilds.emplace_back(child); }

	private:
		list<BT*> mChilds;
	};

	class Selector : public CompositeNode // OR 개념 노드
	{
	public:
		virtual eNodeStatus Run() override;
	};

	class Sequence : public CompositeNode // AND 개념 노드
	{
	public:
		virtual eNodeStatus Run() override;
	};
}