#pragma once
#include "sszScene.h"

namespace ssz
{
    class PrlgScene1 : public Scene
    {
    public:
        PrlgScene1();
        virtual ~PrlgScene1();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnEnter();
        virtual void OnExit();

    private:

    };
}