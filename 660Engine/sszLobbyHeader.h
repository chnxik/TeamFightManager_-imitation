#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class HeaderSlot;

	class LobbyHeader : public UIObject
	{
	public:
		LobbyHeader(const std::wstring& key);
		virtual ~LobbyHeader();

		virtual void Initialize() override;
		virtual void LateUpdate() override;

	private:
		HeaderSlot* mDateSlot;
		HeaderSlot* mGoldSlot;
	};
}