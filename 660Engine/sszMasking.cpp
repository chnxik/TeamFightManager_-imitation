#include "sszMasking.h"
#include "sszApplication.h"
#include "sszRenderer.h"
#include "sszConstantBuffer.h"
#include "sszCamera.h"

#include "sszInput.h"

extern ssz::Application application;

namespace ssz
{
	using namespace ssz::graphics;
	Masking::Masking()
		: mLeftTop{-0.2f, 0.2f, 0.0f}
		, mRightBottom{0.2f, -0.2f, 0.0f}
		, mUseMasking(true)
	{
	}

	Masking::~Masking()
	{
	}

	void Masking::Initialize()
	{
	}

	void Masking::Update()
	{
		// masking area Mouse로 지정
		if (Input::GetKey(eKeyCode::D))
		{
			if (Input::GetKeyDown(eKeyCode::LBUTTON))
			{
				Vector2 MousePos = Input::GetMousePos();
				mLeftTop.x = MousePos.x;
				mLeftTop.y = MousePos.y;
			}

			if (Input::GetKey(eKeyCode::LBUTTON))
			{
				Vector2 MousePos = Input::GetMousePos();
				mRightBottom.x = MousePos.x;
				mRightBottom.y = MousePos.y;
			}

			if (Input::GetKeyUp(eKeyCode::LBUTTON))
			{
				Vector2 MousePos = Input::GetMousePos();
				mRightBottom.x = MousePos.x;
				mRightBottom.y = MousePos.y;
			}
		}
	}

	void Masking::LateUpdate()
	{
	}

	void Masking::Render()
	{
	}

	void Masking::Binds()
	{
		// 윈도우 해상도
		// RECT rect = {};
		// GetClientRect(application.GetHwnd(), &rect);
		// float width = (float)(rect.right - rect.left);
		// float height = (float)(rect.bottom - rect.top);
		// 
		// // 뷰포트 정보
		// Viewport viewport;
		// viewport.width = width;
		// viewport.height = height;
		// 
		// viewport.x = (float)rect.left;
		// viewport.y = (float)rect.top;
		// viewport.minDepth = 0.0f;
		// viewport.maxDepth = 1.0f;

		// 임의 지정 LT, BT
		// LeftTop.x = -0.96f;
		// LeftTop.y = 0.59f;
		// RightBottom.x = 0.96f;
		// RightBottom.y = -0.59f;

		// mask area world -> winpos 변환
		// Vector3 FianlLT = viewport.Project(LeftTop, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);
		// Vector3 FinalRB = viewport.Project(RightBottom, Camera::GetProjectionMatrix(), Camera::GetViewMatrix(), Matrix::Identity);

		Vector3 FianlLT = mLeftTop;
		Vector3 FinalRB = mRightBottom;

		renderer::MaskingCB paCB;
		paCB.Left = FianlLT.x;
		paCB.Top = FianlLT.y;
		paCB.Right = FinalRB.x;
		paCB.Bottom = FinalRB.y;
		paCB.UseMasking = mUseMasking;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Masking];
		cb->SetData(&paCB);
		cb->Bind(eShaderStage::PS);
	}
	void Masking::BindsClear()
	{
		renderer::MaskingCB paCB;
		paCB.UseMasking = 0;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Masking];
		cb->SetData(&paCB);
		cb->Bind(eShaderStage::PS);
	}
	void Masking::SetMaskArea(Vector3 objpos, Vector3 objscale)
	{
		// 윈도우 해상도
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float halfwidth = (float)(rect.right - rect.left) / 2,f;
		float halfheight = (float)(rect.bottom - rect.top) / 2.f;

		Vector3 WinPos = { halfwidth + objpos.x, halfheight - objpos.y, 0.f };
		Vector3 halfScale = { objscale.x / 2.f, objscale.y / 2.f, 0.f };
		
		mLeftTop = { WinPos.x - halfScale.x,WinPos.y - halfScale.y, 0.f };
		mRightBottom = { WinPos.x + halfScale.x, WinPos.y + halfScale.y, 0.f };
	}
}