#include "sszButton.h"

#include "sszGameObject.h"
#include "sszUIObject.h"
#include "sszUIComponent.h"

#include "sszMeshRenderer.h"
#include "sszMaterial.h"
#include "sszResources.h"

#include "sszTexture.h"

namespace ssz
{
	Button::Button()
		: mCurState(eBtnState::Idle)
		, bActive(true)
		, mFunc(nullptr)
		, mInst(nullptr)
		, mDelegateFunc(nullptr)
	{
	}

	Button::~Button()
	{
	}

	void Button::Initialize()
	{
		SetOwnerMaterial();
	}

	void Button::Update()
	{
		

		switch (mCurState)
		{
		case ssz::Button::eBtnState::Idle:
			if (nullptr != mBtnTex[(UINT)eBtnState::Idle])
				mOwnerMaterial->SetTexture(mBtnTex[(UINT)eBtnState::Idle]);
			break;
		case ssz::Button::eBtnState::On:
			if (GetOwnerUI()->IsMouseOn())
			{
				if (nullptr != mBtnTex[(UINT)eBtnState::On])
					mOwnerMaterial->SetTexture(mBtnTex[(UINT)eBtnState::On]);
			}
			else
				mCurState = eBtnState::Idle;
			break;
		case ssz::Button::eBtnState::Down:
			if (nullptr != mBtnTex[(UINT)eBtnState::Down])
				mOwnerMaterial->SetTexture(mBtnTex[(UINT)eBtnState::Down]);
			break;
		}

	}

	
	void Button::SetIdleTex(const std::wstring& TextureKey)
	{
		mBtnTex[(UINT)eBtnState::Idle] = Resources::Find<Texture>(TextureKey);
	}
	
	void Button::SetOnTex(const std::wstring& TextureKey)
	{
		mBtnTex[(UINT)eBtnState::On] = Resources::Find<Texture>(TextureKey);
	}
	
	void Button::SetDownTex(const std::wstring& TextureKey)
	{
		mBtnTex[(UINT)eBtnState::Down] = Resources::Find<Texture>(TextureKey);
	}
	
	void Button::SetOwnerMaterial()
	{
		mOwnerMaterial = GetOwner()->GetComponent<MeshRenderer>()->GetMaterial();
		assert(mOwnerMaterial);
	}

	void Button::MouseLbtnDown()
	{
		mCurState = eBtnState::Down;
	}
	
	void Button::MouseLbtnUp()
	{
		mCurState = eBtnState::Idle;
	}
	
	void Button::MouseLbtnClicked()
	{
		if (nullptr != mFunc)
			mFunc();

		if (mInst && mDelegateFunc)
		{
			(mInst->*mDelegateFunc)();
		}
	}
	
	void Button::MouseOn()
	{
		if(!(GetOwnerUI()->IsLbtnDown()))
			mCurState = eBtnState::On;
	}
}