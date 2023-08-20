#pragma once
#include "sszComponent.h"

namespace ssz
{
	class GameObject;

	class Text : public Component
	{
	public:
		Text();
		~Text();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		void SetFontSize(float Size) { mFontSize = Size; }
		float GetFontSize() { return mFontSize; }

		void SetOffsetPos(Vector3 pos) { mOffsetPos = pos; }
		Vector3 GetOffsetPos() { return mOffsetPos; }

		void SetFontColor(UINT R, UINT G, UINT B, UINT A);

		void SetString(const std::wstring& str) { mString = str; }


		GameObject* GetOwner() { return mOwner; }
		virtual void SetOwner(GameObject* owner) { mOwner = owner; }

	private:
		std::wstring mString;
		Vector3 mFontPos;
		Vector3 mOffsetPos;

		float	mFontSize;
		UINT	mFontColor;
	};
}