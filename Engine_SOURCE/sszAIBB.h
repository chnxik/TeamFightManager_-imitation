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
		T* CreateData(const std::wstring& key) // �ű� ������ �޸� ����
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
				return (T*)(iter->second); // �߰��Ϸ��� key�� ���� ��� return

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

		void RegistRunningNode(BT** ppRunningNode) { mCurRunningBT = ppRunningNode; } // AIBB�� Root_Node�� RunningNode ������ �ּ� ���
		void SetRunningNode(BT* pNode) { (*mCurRunningBT) = pNode; } // ��ϵ� RunningNode ������(Root_Node RunningNode)�� Running Node ���

	private:
		std::map<std::wstring, void*> mAddedData;
		std::map<std::wstring, void*> mCreatedData;
		BT** mCurRunningBT;
	};
}