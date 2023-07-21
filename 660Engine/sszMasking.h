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

	private:
		Vector3 LeftTop;
		Vector3 RightBottom;
	};
}