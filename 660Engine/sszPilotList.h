#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class PilotList
	{
	public:
		PilotList();
		~PilotList();

		void Initialize();

		Pilot* GetPilot(const std::wstring& key);
		// 데이터를 찾아오는 함수.

	private:
		std::map<std::wstring, Pilot*> mPilotMap;
	};
}