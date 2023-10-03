#pragma once
#include "sszUIObject.h"
#include "GameEnums.h"

namespace ssz
{
	class LineUpTeamTitle : public UIObject
	{
	public:
		LineUpTeamTitle(const std::wstring & key);
		virtual ~LineUpTeamTitle();

		virtual void Initialize() override;

		void SetTitleType(eCampType eCamp, eTeamColor eColor);

	private:
		std::wstring TitleTex[(UINT)eCampType::End][(UINT)eTeamColor::End];
	};

}