#pragma once
#include "CommonObjHeader.h"

namespace ssz
{
	class ChampList
	{
	public:
		ChampList();
		~ChampList();

		void Initialize();

		Champ* GetChamp(const std::wstring& key);

	private:
		std::map<std::wstring, Champ*> mChampMap;
	};
}