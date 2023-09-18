#pragma once
#include "sszGameObject.h"

namespace ssz
{
    class CloudObj :
        public GameObject
    {
    public:
        enum class eDayTime
        {
            Day,
            Sunset,
            Night,
            End,
        };

        CloudObj();
        virtual ~CloudObj();

        virtual void Initialize();
        virtual void Update();

        void SetMt(UINT idx);
        void SetDayTime(eDayTime daytime) { mDayTime = daytime; }

    private:
        float vPlayArea;

        bool bPlay;
        bool bReady;

        float fReadyTime;
        float fRatio;

        float fSpeed;
        eDayTime mDayTime;

        std::shared_ptr<Texture> CloudeTexture[(UINT)eDayTime::End][8];
    };
}