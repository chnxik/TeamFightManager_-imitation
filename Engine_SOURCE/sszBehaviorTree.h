#pragma once
#include "sszEngine.h"

namespace ssz::AI
{
	using namespace std;

	enum class eNodeStatus
	{
		SUCCESS, // ����
		FAILURE, // ����
		RUNNING // ������
	};

	class BT // Base ���
	{
	public:
		BT();
		virtual ~BT();

		virtual bool Run() = 0;

	private:
		list<BT*> mChild;

		friend class CompositeNode;
	};

	class CompositeNode : public BT // ���ճ��
	{
	public:
		const list<BT*>& getChild() const { return mChild; }
		void addChild(BT* child) { mChild.emplace_back(child); }
	};

	class Selector : public CompositeNode // OR ���� ���
	{
	public:
		virtual bool Run() override;
	};

	class Sequence : public CompositeNode // AND ���� ���
	{
	public:
		virtual bool Run() override;
	};
}