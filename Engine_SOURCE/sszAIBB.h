#pragma once
#include "sszEngine.h"

namespace ssz::AI
{
	class BT;
	class AIBB
	{
	public:
		AIBB();
		~AIBB();

		template <typename T>
		T* CreateData(const std::wstring& key) // 신규 데이터 메모리 생성
		{
			std::map<std::wstring, void*>::iterator iter
				= mCreatedData.find(key);
			
			if (iter != mCreatedData.end())
				return (T*)(iter->second);
			
			T* Data = new T();

			mCreatedData.insert(std::make_pair(key, Data));

			return Data;
		}

		template <typename T>
		T* AddData(const std::wstring& key, T* data)
		{
			std::map<std::wstring, void*>::iterator iter
				= mAddedData.find(key);

			if (iter != mAddedData.end())
				return (T*)(iter->second); // 추가하려는 key가 있을 경우 return

			mAddedData.insert(std::make_pair(key, data));

			iter = mAddedData.find(key);

			return (T*)(iter->second);
		}
		
		template <typename T>
		T* FindData(const std::wstring& key)
		{
			std::map<std::wstring, void*>::iterator iter
				= mAddedData.find(key);

			if (iter != mAddedData.end())
				return	(T*)(iter->second);

			iter = mCreatedData.find(key);

			if (iter != mCreatedData.end())
				return (T*)(iter->second);

			return nullptr;
		}

		void ClearAllData();

		void RegistRunningNode(BT** ppRunningNode) { mCurRunningBT = ppRunningNode; } // AIBB에 Root_Node의 RunningNode 포인터 주소 등록
		void SetRunningNode(BT* pNode) { (*mCurRunningBT) = pNode; } // 등록된 RunningNode 포인터(Root_Node RunningNode)에 Running Node 등록

	private:
		std::map<std::wstring, void*> mAddedData;
		std::map<std::wstring, void*> mCreatedData;
		BT** mCurRunningBT;
	};
}