#include "sszButtonUI.h"

#include "sszInput.h"

#include "sszGameObject.h"

#include "sszUIObject.h"
#include "sszUIComponent.h"

#include "sszMeshRenderer.h"
#include "sszMaterial.h"
#include "sszResources.h"

#include "sszTexture.h"

namespace ssz
{
	ButtonUI::ButtonUI()
		: mCurState(eBtnState::Idle)
		, mType(eBtnType::Push)
		, bActive(true)
		, mFunc(nullptr)
		, mInst(nullptr)
		, mDelegateFunc(nullptr)
		, mDelegateWFunc(nullptr)
		, mOwnerMaterial(nullptr)
	{
	}

	ButtonUI::~ButtonUI()
	{
	}

	void ButtonUI::Initialize()
	{
		SetOwnerMaterial();
		GetOwner()->AddComponent<Collider2D>()->Initialize();
	}

	void ButtonUI::Update()
	{
		if (!mOwnerMaterial)
			return;
		
		bool bMouseOn = GetOwnerUI()->IsMouseOn();

		ChangeBtnTex(mCurState);

		if (mCurState == eBtnState::On && !bMouseOn)
			SetBtnState(eBtnState::Idle);

		// Down �����ε� ��ư �ܺο��� Ŭ���� �����ƴ�.
		if (mCurState == eBtnState::Down)
		{
			if (ssz::Input::GetKeyDown(eKeyCode::LBUTTON) && !bMouseOn)
			{
				// ���� �����ִ� �˾��� �ݴ� ���±���� �̺κп� �߰�
				SetBtnState(eBtnState::Idle);
			}
		}

	}

	
	void ButtonUI::SetIdleTex(const std::wstring& TextureKey)
	{
		mBtnTex[(UINT)eBtnState::Idle] = Resources::Find<Texture>(TextureKey);
	}
	
	void ButtonUI::SetOnTex(const std::wstring& TextureKey)
	{
		mBtnTex[(UINT)eBtnState::On] = Resources::Find<Texture>(TextureKey);
	}
	
	void ButtonUI::SetDownTex(const std::wstring& TextureKey)
	{
		mBtnTex[(UINT)eBtnState::Down] = Resources::Find<Texture>(TextureKey);
	}
	
	bool ButtonUI::ChangeBtnTex(eBtnState eState)
	{
		if (nullptr != mBtnTex[(UINT)eState])
		{
			mOwnerMaterial->SetTexture(mBtnTex[(UINT)eState]);
			return true;
		}
		
		return false;
	}

	void ButtonUI::SetOwnerMaterial()
	{
		mOwnerMaterial = GetOwner()->GetComponent<MeshRenderer>()->GetMaterial();
		assert(mOwnerMaterial);
	}

	void ButtonUI::MouseLbtnDown()
	{
		switch (mType)
		{
		case ssz::ButtonUI::eBtnType::Selected:
			break;
		case ssz::ButtonUI::eBtnType::Push:
			mCurState = eBtnState::Down;
			break;
		}
	}
	
	void ButtonUI::MouseLbtnUp()
	{
		switch (mType)
		{
		case ssz::ButtonUI::eBtnType::Selected:
			break;
		case ssz::ButtonUI::eBtnType::Push:
			mCurState = eBtnState::Idle;
			break;
		}
	}
	
	void ButtonUI::MouseLbtnClicked()
	{
		switch (mType)
		{
		case ssz::ButtonUI::eBtnType::Selected:
			mCurState = eBtnState::Down;
			break;
		case ssz::ButtonUI::eBtnType::Push:
			break;
		}

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
	
	void ButtonUI::MouseOn()
	{
		bool bLbtnDown = GetOwnerUI()->IsLbtnDown();

		if(!bLbtnDown)
			mCurState = eBtnState::On;
	}
}