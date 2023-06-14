#include "sszPlayer.h"
#include "sszTime.h"
#include "sszInput.h"

#define MAXCOLOR 0.8f

namespace ssz
{
	Player::Player()
		: mColorChange{ 1.f,1.f,1.f,1.f }
		, mFinalColor{}
		, mFinalRadius(0.f)
		, mfColorAcc(0.f)
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
	}

	void Player::Update()
	{
		Vector4 Pos = GetPos();

		// 플레이어 객체 이동

		if (Pos.y < 0.2f && ssz::Input::GetKey(ssz::eKeyCode::UP)) { Pos.y += 0.2f * (float)ssz::Time::DeltaTime(); }
		if (Pos.y > -0.2f && ssz::Input::GetKey(ssz::eKeyCode::DOWN)) { Pos.y -= 0.2f * (float)ssz::Time::DeltaTime(); }
		if (Pos.x < 0.2f && ssz::Input::GetKey(ssz::eKeyCode::RIGHT)) { Pos.x += 0.2f * (float)ssz::Time::DeltaTime(); }
		if (Pos.x > -0.2f && ssz::Input::GetKey(ssz::eKeyCode::LEFT)) { Pos.x -= 0.2f * (float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::SPACE)) { Pos.z = 0.02f; }

		// 플레이어 객체 습득시 도달 크기까지 서서히 증가
		if (Pos.z < mFinalRadius)
			Pos.z += 0.05f * (float)ssz::Time::DeltaTime();

		SetPos(Pos);

		// 색상 변환

		Vector4 Color = GetColor();
		
		if (0.f < mfColorAcc)
		{
			Color.x = mFinalColor.x + (0.8f - mFinalColor.x) * mfColorAcc;
			Color.y = mFinalColor.y + (0.8f - mFinalColor.y) * mfColorAcc;
			Color.z = mFinalColor.z + (0.8f - mFinalColor.z) * mfColorAcc;
			mfColorAcc -= 3.5f * (float)ssz::Time::DeltaTime();
		}
		else
		{
			mfColorAcc = 0.f;
			Color = mFinalColor;
		}

		// 무작위 변환
		/*
		Color.x += 0.2f * mColorChange.x * (float)ssz::Time::DeltaTime();
		Color.y += 0.5f * mColorChange.y * (float)ssz::Time::DeltaTime();
		Color.z += 0.9f * mColorChange.z * (float)ssz::Time::DeltaTime();

		if (MAXCOLOR < Color.x)
		{
			mColorChange.x *= -1.f;
			Color.x = MAXCOLOR - (Color.x - MAXCOLOR);
		}
		else if (0.f >= Color.x)
		{
			mColorChange.x *= -1.f;
			Color.x = 0.f - Color.x;
		}
		
		if (MAXCOLOR < Color.y)
		{
			mColorChange.y *= -1.f;
			Color.y = MAXCOLOR - (Color.y - MAXCOLOR);
		}
		else if (0.f >= Color.y)
		{
			mColorChange.y *= -1.f;
			Color.y = 0.f - Color.y;
		}

		if (MAXCOLOR < Color.z)
		{
			mColorChange.z *= -1.f;
			Color.z = MAXCOLOR - (Color.z - MAXCOLOR);
		}
		else if (0.f >= Color.z)
		{
			mColorChange.z *= -1.f;
			Color.z = 0.f - Color.z;
		}
		*/
		SetColor(Color);
	}

	void Player::LateUpdate()
	{
	}

	void Player::Render()
	{
		Circle::Render();
	}
	void Player::SetFinalRadius(float radius)
	{
		mFinalRadius = radius;
	}
	void Player::AddRadius(float radius)
	{
		mFinalRadius += radius;
	}
}