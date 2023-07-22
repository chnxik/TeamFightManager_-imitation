#pragma once
#include "sszEngine.h"

namespace ssz
{
	using namespace std;

	class BT
	{
	public:
		virtual bool Run() = 0;
	};

	class CompositeNode : public BT
	{
	public:
		CompositeNode();
		virtual ~CompositeNode();

		const list<BT*>& getChild() const { return mChild; }
		void addChild(BT* child)
		{
			mChild.emplace_back(child);
		}

	private:
		list<BT*> mChild;
	};

	class Selector : public CompositeNode
	{
	public:
		virtual bool Run() override;
	};

	class Sequence : public CompositeNode
	{
	public:
		virtual bool Run() override;
	};
}