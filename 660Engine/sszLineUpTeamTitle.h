#pragma once
#include "sszUIObject.h"


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
		std::shared_ptr<Texture> TitleTex[(UINT)eCampType::End][(UINT)eTeamColor::End];
	};

}