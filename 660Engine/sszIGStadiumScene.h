#pragma once
#include "..\Engine_SOURCE\sszScene.h"

namespace ssz
{
	class IGStadiumScene : public Scene
	{
	public:
		IGStadiumScene();
		virtual ~IGStadiumScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:

	};
}