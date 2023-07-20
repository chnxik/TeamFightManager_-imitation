#pragma once
#include "sszComponent.h"
#include "sszAnimation.h"

namespace ssz
{
    class Animator : public Component
    {
    public:
        struct Event
        {
            void operator=(std::function<void()> func)
            {
                mEvent = std::move(func);
            }
            
            void operator()()
            {
                if (mEvent)
                    mEvent();
            }

            std::function<void()> mEvent;
        };

        struct Events
        {
            Event startEvent;
            Event complateEvent;
            Event endEvent;
        };

        Animator();
        ~Animator();

        virtual void Initialize();
        virtual void Update();
        virtual void LateUpdate();
        virtual void Render();

        void Create(std::wstring name
            , std::shared_ptr<graphics::Texture> atlas
            , Vector2 leftTop
            , Vector2 size
            , UINT columnLength
            , Vector2 offset = Vector2::Zero
            , float duration = 0.f);

    private:
        std::map<std::wstring, Animation*> mAnimations;
        std::map<std::wstring, Events*> mEvents;
        Animation* mActiveAnimation;

        bool mbLoop;
    };
}