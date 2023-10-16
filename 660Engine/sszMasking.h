#pragma once
#include "sszScript.h"

namespace ssz
{
	class Masking : public Script
	{
	public:
		Masking();
		~Masking();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void Binds() override;
		virtual void BindsClear() override;

		void SetMaskArea(Vector3 objpos, Vector3 objscale);
		void UseMasking() { mUseMasking = true; }
		void StopMasking() { mUseMasking = false; }

	private:
		Vector3 mLeftTop;
		Vector3 mRightBottom;
		bool	mUseMasking;
	};
}