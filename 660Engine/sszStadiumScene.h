#pragma once
#include "..\Engine_SOURCE\sszScene.h"

namespace ssz
{
	class StadiumScene : public Scene
	{
	public:
		StadiumScene();
		virtual ~StadiumScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
	};
}