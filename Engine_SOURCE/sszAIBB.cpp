#include "sszAIBB.h"

namespace ssz::AI
{
	AIBB::AIBB()
		: mCurRunningBT(nullptr)
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
	}

	void AIBB::ClearAllData()
	{
		std::map<std::wstring, void*>::iterator iter = mCreatedData.begin();
		while (iter != mCreatedData.end())
		{
			delete iter->second;
			iter = mCreatedData.erase(iter);
		}
	}
}