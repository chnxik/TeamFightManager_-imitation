#pragma once
#include "sszScene.h"

namespace ssz
{
	class PrlgScene3 : public Scene
	{
    public:
        PrlgScene3();
        virtual ~PrlgScene3();

        virtual void Initialize() override;
        virtual void Update() override;
        virtual void LateUpdate() override;
        virtual void Render() override;

        virtual void OnEnter();
        virtual void OnExit();

    private:

	};
}