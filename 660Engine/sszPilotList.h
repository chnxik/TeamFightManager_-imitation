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
		// �����͸� ã�ƿ��� �Լ�.

	private:
		std::map<std::wstring, Pilot*> mPilotMap;
	};
}