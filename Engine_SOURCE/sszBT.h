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
		BT() : mAIBB(nullptr) {}
		BT(std::shared_ptr<AIBB> pAIBB) : mAIBB(pAIBB) {}
		virtual ~BT();

		virtual eNodeStatus Run() = 0;

	protected:
		std::shared_ptr<AIBB> mAIBB;
	};

	// ============================ Root Node ==============================

	class Root_Node : public BT // �Ѹ� ���
	{
	public:
		virtual ~Root_Node();
		Root_Node() : mChild(nullptr) {};
		Root_Node(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB), mChild(nullptr) {}

		BT* GetChild() { return mChild; }

		template<typename T>
		T* AddChild()
		{
			T* NewNode = new T();

			mChild = dynamic_cast<BT*>(NewNode);

			if (mChild == nullptr)
				return nullptr;

			return NewNode;
		}

		virtual eNodeStatus Run();

	private:
		BT* mChild;
	};

	// ============================ Decorate Node =========================
	class Decorate_Node : public BT
	{
	public:
		virtual ~Decorate_Node();

		BT* GetChild() { return mChild; }

		template<typename T>
		T* AddChild()
		{
			T* NewNode = new T();

			mChild = dynamic_cast<BT*>(NewNode);

			if (mChild == nullptr)
				return nullptr;

			return NewNode;
		}

		virtual eNodeStatus Run() = 0;

	private :
		BT* mChild;
	};

	// �ݵ�� ������ ��ȯ
	class AllSuccess_Node : public Decorate_Node
	{
	public:
		virtual eNodeStatus Run()
		{
			GetChild()->Run();

			return NS_SUCCESS;
		}
	};

	// ������ ��ȯ�� �� ���� �ݺ�
	class Until_Node : public Decorate_Node
	{
	public:
		virtual eNodeStatus Run()
		{
			while (GetChild()->Run() != NS_SUCCESS)
			{
			}
		}
	};

	

	// ============================= Condition Node ===================================
	class Condition_Node : public BT // ����� �Ǵ� ���
	{
	public:
		Condition_Node(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}

		virtual eNodeStatus Run() = 0;
	};

	// ========================================== Composite Node =================================

	class Composite_Node : public BT // ���ճ��
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

			mChilds.emplace_back(childNode);

			return NewNode;
		}

		template <typename T>
		T* AddChild(std::shared_ptr<AIBB> pAIBB)
		{
			T* NewNode = new T(pAIBB);

			BT* childNode = dynamic_cast<BT*>(NewNode);

			if (childNode == nullptr)
				return nullptr;

			mChilds.emplace_back(childNode);

			return NewNode;
		}

	private:
		list<BT*> mChilds;
	};

	class Selector_Node : public Composite_Node // OR ���� ���
	{
	public:
		virtual eNodeStatus Run() override;
	};

	class Sequence_Node : public Composite_Node // AND ���� ���
	{
	public:
		virtual eNodeStatus Run() override;
	};

		
	class RdSelector_Node : public Composite_Node // �� ���ึ�� �ڽĳ���� ������ ���� (������)
	{
	public:
		virtual eNodeStatus Run() override;
	};

	// =========================================== Leaf Node ======================================

	class Action_Node : public BT	// �ൿ ���� ���
	{
	public:
		Action_Node(std::shared_ptr<AIBB> pAIBB) : BT(pAIBB) {}

		virtual eNodeStatus Run() = 0;
	};
}