#pragma once
#include "sszScene.h"
#include "sszGameObject.h"

namespace ssz
{
	class LobbyHeader;
	class CloudObj;
	class ProceedBtn;

	class MainLobbyScene : public Scene
	{
	public:
		MainLobbyScene();
		virtual ~MainLobbyScene();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		virtual void OnEnter() override;
		virtual void OnExit() override;

		void DayTimeSetting();

	private:
		GameObject* BgSky;
		LobbyHeader* mLobbyheader;
		ProceedBtn* mProceedBtn;

		CloudObj* mCloud[8];
	};
}