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
		bool CreateData(const std::wstring& key) // �ű� ������ �޸� ����
		{
			T* Data = new T();

			std::map<std::wstring, void*>::iterator iter
				= mCreatedData.find(key);

			if (iter != mCreatedData.end())
				return false;

			mCreatedData.insert(std::make_pair(key, Data));

			return true;
		}

		template <typename T>
		bool AddData(const std::wstring& key, T* data)
		{
			std::map<std::wstring, void*>::iterator iter
				= mAddedData.find(key);

			if (iter != mAddedData.end())
				return false; // �߰��Ϸ��� key�� ���� ��� return

			mAddedData.insert(std::make_pair(key, data));
			return true;
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
		

	private:
		std::map<std::wstring, void*> mAddedData;
		std::map<std::wstring, void*> mCreatedData;
		BT* mRunningBT;
	};
}