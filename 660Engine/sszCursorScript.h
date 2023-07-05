#pragma once
#include <sszScript.h>

namespace ssz
{
	class CursorScript : public Script
	{
	public:
		CursorScript();
		virtual ~CursorScript();
		virtual void Initialize() override;
		virtual void LateUpdate() override;

	private:
		Vector2 CursorSize;
	};
}