#include "sszBlackboard.h"

namespace ssz::AI
{
	AIBB::AIBB()
		: mRunningBT(nullptr)
	{
	}

	AIBB::~AIBB()
	{
		std::map<std::wstring, void*>::iterator iter = mCreatedData.begin();
		while (iter != mCreatedData.end())
		{
			delete iter->second;
			iter = mCreatedData.erase(iter);
		}

		if (mRunningBT)
		{
			delete mRunningBT;
			mRunningBT = nullptr;
		}
	}

}