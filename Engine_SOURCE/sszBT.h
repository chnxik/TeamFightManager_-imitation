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
		SUCCESS,	// ����
		FAILURE,	// ����
		RUNNING,	// ������
		INVALID		// ��ȿ���� ����
	};

	// ============================ ���̽� ==============================

	class BT // Base ���
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

	// ============================ Root Node ==============================

	class Root : public BT // �Ѹ� ���
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

	// ============================= Condition Node ===================================
	class Condition : public BT // ����� �Ǵ� ���
	{
	public:
		Condition(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}

		virtual eNodeStatus Run() = 0;
	};

	// ========================================== Composite Node =================================

	class CompositeNode : public BT // ���ճ��
	{
	public:
		virtual ~CompositeNode();

		const list<BT*>& GetChilds() const { return mChilds; }
		void AddChild(BT* child) { mChilds.emplace_back(child); }

	private:
		list<BT*> mChilds;
	};

	class Selector : public CompositeNode // OR ���� ���
	{
	public:
		virtual eNodeStatus Run() override;
	};

	class Sequence : public CompositeNode // AND ���� ���
	{
	public:
		virtual eNodeStatus Run() override;
	};

	// =========================================== Leaf Node ======================================

	class Action : public BT	// �ൿ ���� ���
	{
	public:
		Action(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}

		virtual eNodeStatus Run() = 0;
	};
}