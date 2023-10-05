#pragma once
#include "sszSelectBtnUI.h"

#include "sszInput.h"
#include "sszTexture.h"
#include "sszResources.h"

namespace ssz
{
	SelectBtnUI::SelectBtnUI()
		: mCheckSelected(nullptr)
		
	{
	}

	SelectBtnUI::~SelectBtnUI()
	{
	}
	
	void SelectBtnUI::SetSelTempTex(const std::wstring& TextureKey)
	{
		mSelTempTex = Resources::Find<Texture>(TextureKey);
	}
	
	void SelectBtnUI::SetSelTempTex(std::shared_ptr<Texture> Texture)
	{
		mSelTempTex = Texture;
	}

	void SelectBtnUI::MouseLbtnDown()
	{
		if (*mCheckSelected == (UIObject*)GetOwner())
			return;

		if ((*mCheckSelected) != nullptr)
		{
			(*mCheckSelected)->GetComponent<SelectBtnUI>()->SwitchingSelectTex();
		}

		*mCheckSelected = (UIObject*)GetOwner();
		
		SwitchingSelectTex();
		mCurState = eBtnState::On;

		if (nullptr != mFunc)
			mFunc();

		if (mInst && mDelegateFunc)
		{
			(mInst->*mDelegateFunc)();
		}
		else if (mInst && mDelegateWFunc)
		{
			(mInst->*mDelegateWFunc)(mDelegateKey);
		}
	}
	
	void SelectBtnUI::MouseLbtnUp()
	{
		mCurState = eBtnState::Idle;
	}
	
	void SelectBtnUI::SwitchingSelectTex()
	{
		std::shared_ptr<Texture> Temp = mBtnTex[(UINT)eBtnState::On];
		mBtnTex[(UINT)eBtnState::On] = mSelTempTex;
		mSelTempTex = Temp;
	}
	
	void SelectBtnUI::Update()
	{
		if (!mOwnerMaterial)
			return;

		bool bMouseOn = GetOwnerUI()->IsMouseOn();

		if (bMouseOn && !bPrevMouseOn)
		{
			((UIObject*)GetOwner())->MouseUp();
			bPrevMouseOn = true;
		}
		else if (bPrevMouseOn && !bMouseOn)
		{
			((UIObject*)GetOwner())->MouseAway();
			bPrevMouseOn = false;
		}


		if (*mCheckSelected == (UIObject*)GetOwner() && !bMouseOn)
		{
			mCurState = eBtnState::Down;
		}

		else if (*mCheckSelected != (UIObject*)GetOwner() && !bMouseOn)
		{
			mCurState = eBtnState::Idle;
		}

		// Down 상태인데 버튼 외부에서 클릭이 감지됐다.
		// 필요없음

		ChangeBtnTex(mCurState);
	}
}