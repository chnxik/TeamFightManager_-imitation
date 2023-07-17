#pragma once
#include "sszUIComponent.h"
#include "sszTexture.h"
#include "sszMaterial.h"

typedef void(*voidFunc)(void);
typedef void(ssz::Entity::* DELEGATE)(void); // Entity�� ��ӹ��� ��� Ŭ������ �Լ��� ȣ���� �� �ִ� �Լ�������.
typedef void(ssz::Entity::* DELEGATEW)(const std::wstring&);

namespace ssz
{

	class Button : public UIComponent
	{
	public:
		enum class eBtnState
		{
			Idle,
			On,
			Down,
			End,
		};

		Button();
		virtual ~Button();

	public:
		virtual void Initialize();
		virtual void Update();

		void SetvoidFunc(voidFunc pCallBack) { mFunc = pCallBack; }
		void SetDelegate(Entity* Inst, DELEGATE Func) { mInst = Inst; mDelegateFunc = Func; }
		void SetDelegateW(Entity* Inst, DELEGATEW Func, const std::wstring& key) 
		{
			mInst = Inst; 
			mDelegateWFunc = Func; 
			mDelegateKey = key;
		}

		void SetIdleTex(const std::wstring& TextureKey);
		void SetOnTex(const std::wstring& TextureKey);
		void SetDownTex(const std::wstring& TextureKey);

		void SetActive(bool b) { bActive = b; }
		void SetOwnerMaterial();

		virtual void MouseLbtnDown() override;
		virtual void MouseLbtnUp() override;
		virtual void MouseLbtnClicked() override;
		virtual void MouseOn() override;

	private:
		std::shared_ptr<Texture> mBtnTex[(UINT)eBtnState::End];

		std::shared_ptr<Material> mOwnerMaterial;

		eBtnState mCurState;

		bool bActive;

		voidFunc mFunc;

		Entity* mInst; // �Լ��� ȣ�� �� ��ü
		DELEGATE mDelegateFunc; // �Լ��� ��Ƴ��� �Լ�������
		DELEGATEW mDelegateWFunc; // �Լ��� ��Ƴ��� �Լ�������
		std::wstring mDelegateKey;
	};
}