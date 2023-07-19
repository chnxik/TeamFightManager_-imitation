#pragma once
#include "sszUIObject.h"

namespace ssz
{
	class LineUpTeamTitle : public UIObject
	{
	public:
		enum eCampType
		{
			Player,
			Enemy,
		};

		enum eColorType
		{
			Red,
			Blue
		};

		LineUpTeamTitle(const std::wstring & key);
		virtual ~LineUpTeamTitle();

		void SetTitleType(eCampType eCamp, eColorType eColor);

	private:
		std::shared_ptr<Texture> TitleTex[2][2];
	};

}