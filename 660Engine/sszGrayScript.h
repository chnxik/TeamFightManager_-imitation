#pragma once
#include "sszScript.h"

namespace ssz
{
	class GrayScript : public Script
	{
	public:
		GrayScript();
		~GrayScript();

		virtual void Binds() override;
		virtual void BindsClear() override;

		void UseGrayScript() { useGray = true; }
		void StopGrayScript() { useGray = false; }

		void UseAlphaScript() { useAlpha = true; }
		void StopAlphaScript() { useAlpha = false; }

		void SetGrayRatio(float ratio) { grayRatio = ratio; }
		void SetAlphaRatio(float ratio) { AlphaRatio = ratio; }

	private:
		bool useGray;
		bool useAlpha;

		float grayRatio;
		float AlphaRatio;
	};
}