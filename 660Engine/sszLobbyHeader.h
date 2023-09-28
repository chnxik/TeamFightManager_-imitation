#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class Text;

	class HeaderSlot;

	class LobbyHeader : public UIObject
	{
	public:
		LobbyHeader(const std::wstring& key);
		virtual ~LobbyHeader();

		virtual void Initialize() override;
		virtual void LateUpdate() override;

		void UpdateEnterScene();

	private:
		HeaderSlot* mDateSlot;
		HeaderSlot* mGoldSlot;
		Text* mTeamName;
		Text* mTeamRecord;
	};
}