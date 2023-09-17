#pragma once
#include "sszButtonUI.h"

namespace ssz
{
    class SelectBtnUI :
        public ButtonUI
    {
    public:
        SelectBtnUI();
        virtual ~SelectBtnUI();

        void InitCheckSelected(UIObject** ObjAddress) { mCheckSelected = ObjAddress; }

        virtual void Update() override;

        void SetSelTempTex(const std::wstring& TextureKey);
        void SetSelTempTex(std::shared_ptr<Texture> Texture);

        virtual void MouseLbtnDown() override;
        virtual void MouseLbtnUp() override;
        virtual void MosueLbtnClicked() {};

        void SwitchingSelectTex();

    private:
        std::shared_ptr<Texture> mSelTempTex;

        UIObject** mCheckSelected;

    };
}