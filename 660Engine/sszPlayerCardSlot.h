#pragma once
#include "sszUIObject.h"
namespace ssz
{
	class PlayerCardSlot : public UIObject
	{
	public:
		PlayerCardSlot(const std::wstring& key);
		virtual ~PlayerCardSlot();

		void SetRed();
		void SetBlue();

	private:
		enum eColor
		{
			Red,
			Blue,
		};

		enum eSlotState
		{
			Idle,
			highlighted
		};

		std::shared_ptr<Texture> vecCardTex[2][2];
	};
}