#pragma once
#include "sszEngine.h"

namespace ssz::AI
{
	class Blackboard
	{
	public:
		template <typename T>
		static bool CreateData(const std::wstring& key) // �ű� ������ �޸� ����
		{
			T* Data = new T();

			std::map<std::wstring, void*>::iterator iter
				= mData.find(key);

			if (iter != mData.end())
				return false;

			mData.insert(std::make_pair(key, Data));

			return true;
		}

		template <typename T>
		static bool AddData(const std::wstring& key, T* data)
		{
			std::map<std::wstring, void*>::iterator iter
				= mData.find(key);

			if (iter != mData.end())
				return false; // �߰��Ϸ��� key�� ���� ��� return

			mData.insert(std::make_pair(key, data));
			return true;
		}
		
		template <typename T>
		static T* FindData(const std::wstring& key)
		{
			std::map<std::wstring, void*>::iterator iter
				= mData.find(key);

			if (iter == mData.end())
				return nullptr;
			
			return	(T*)(iter->second);
		}
		

	private:
		static std::map<std::wstring, void*> mData;

	};
}