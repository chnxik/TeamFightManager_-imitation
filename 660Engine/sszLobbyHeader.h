#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class LobbyHeader : public UIObject
	{
	public:
		LobbyHeader(const std::wstring& key);
		virtual ~LobbyHeader();

		virtual void Initialize() override;
	private:
	};
}