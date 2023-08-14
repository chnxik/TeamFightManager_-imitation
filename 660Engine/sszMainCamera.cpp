#include "sszMainCamera.h"
#include "CommonObjHeader.h"

namespace ssz
{
	GameObject* MainCamera::mMainCamera = nullptr;

	void MainCamera::Initialize()
	{
		mMainCamera = new GameObject();
		Transform* tr = mMainCamera->GetComponent<Transform>();

		Vector3 Pos(0.f, 0.f, -10.f);

		tr->SetPosition(Pos);

		mMainCamera->SetName(L"MainCamera");
		mMainCamera->AddComponent<Camera>();

	}
	void MainCamera::RegistCamera(Scene* pActiveScene)
	{
		pActiveScene->AddGameObject(enums::eLayerType::Camera, mMainCamera);
	}
}