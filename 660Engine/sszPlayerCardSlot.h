#pragma once
#include "sszUIObject.h"
#include "sszTexture.h"
#include "GameEnums.h"

namespace ssz
{
	using namespace ssz::graphics;

	class PlayerCardSlot : public UIObject
	{
	public:
		PlayerCardSlot(const std::wstring& key);
		virtual ~PlayerCardSlot();

		virtual void Initialize() override;

		void SetRed();
		void SetBlue();

	private:
		std::shared_ptr<Texture> vecCardTex[(UINT)eTeamColor::End][(UINT)eSlotState::End];
	};
}