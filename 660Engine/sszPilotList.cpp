#include "sszPilotList.h"

namespace ssz
{
    PilotList::PilotList()
    {
    }

    PilotList::~PilotList()
    {
        std::map<std::wstring, Pilot*>::iterator iter = mPilotMap.begin();

        while (iter != mPilotMap.end())
        {
            delete iter->second;
            iter = mPilotMap.erase(iter);
        }
    }

    void PilotList::Initialize()
    {
    }
    
    Pilot* PilotList::GetPilot(const std::wstring& key)
    {
        std::map<std::wstring, Pilot*>::iterator iter = mPilotMap.find(key);

        if (iter != mPilotMap.end())
            return iter->second;

        return nullptr;
    }
}