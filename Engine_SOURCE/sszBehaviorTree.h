#pragma once
#include "sszEngine.h"

namespace ssz::AI
{
	using namespace std;

	enum class eNodeStatus
	{
		SUCCESS, // 성공
		FAILURE, // 실패
		RUNNING // 진행중
	};

	class BT // Base 노드
	{
	public:
		BT();
		virtual ~BT();

		virtual bool Run() = 0;

	private:
		list<BT*> mChild;

		friend class CompositeNode;
	};

	class CompositeNode : public BT // 복합노드
	{
	public:
		const list<BT*>& getChild() const { return mChild; }
		void addChild(BT* child) { mChild.emplace_back(child); }
	};

	class Selector : public CompositeNode // OR 개념 노드
	{
	public:
		virtual bool Run() override;
	};

	class Sequence : public CompositeNode // AND 개념 노드
	{
	public:
		virtual bool Run() override;
	};
}