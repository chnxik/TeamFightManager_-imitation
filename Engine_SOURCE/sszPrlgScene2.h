#pragma once
#include "sszScene.h"

namespace ssz
{
	class PrlgScene2 : public Scene
	{
    public:
        PrlgScene2();
        virtual ~PrlgScene2();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnEnter();
        virtual void OnExit();

    private:

	};
}