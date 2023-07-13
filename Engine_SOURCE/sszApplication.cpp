#include "sszApplication.h"
#include "sszInput.h"
#include "sszTime.h"
#include "sszRenderer.h"
#include "sszSceneManager.h"
#include "..\660Engine\Load.h"

namespace ssz
{
	Application::Application()
		: graphicDevice(nullptr)
		, mHwnd(NULL)
		, mWidth(-1)
		, mHeight(-1)
	{

	}

	Application::~Application()
	{
		
	}

	void Application::Run()
	{
		Update();
		LateUpdate();
		Render();
		Destory();
	}

	void Application::Initialize()
	{
		Time::Initiailize();
		Input::Initialize();

		renderer::Initialize();
		ssz::InitializeScenes();
	}

	void Application::Update()
	{
		Time::Update();
		Input::Update();
		SceneManager::Update();
	}

	void Application::LateUpdate()
	{
		SceneManager::LateUpdate();
	}

	void Application::Render()
	{
		Time::Render();

		graphicDevice->ClearTarget();
		graphicDevice->UpdateViewPort();

		renderer::Render();
	}

	void Application::Destory()
	{
		SceneManager::Destroy();
	}

	void Application::Present()
	{
		graphicDevice->Present();
		renderer::CameraClear();
	}

	void Application::Release()
	{
		renderer::Release();
		SceneManager::Release();
	}

	void Application::SetWindow(HWND hwnd, UINT width, UINT height)
	{
		if (graphicDevice == nullptr)
		{
			mHwnd = hwnd;
			mWidth = width;
			mHeight = height;

			graphicDevice = std::make_unique<ssz::graphics::GraphicDevice_Dx11>();
			ssz::graphics::GetDevice() = graphicDevice.get();
		}

		RECT rt = { 0, 0, (LONG)width , (LONG)height };
		AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, false);
		SetWindowPos(mHwnd, nullptr, 0, 0, rt.right - rt.left, rt.bottom - rt.top, 0);
		ShowWindow(mHwnd, true);
 		UpdateWindow(mHwnd);
	}
}
