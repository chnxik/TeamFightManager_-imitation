#include "sszPlayer.h"
#include "sszTime.h"
#include "sszInput.h"

#define MAXCOLOR 0.8f

namespace ssz
{
	Player::Player()
		: mColorChange{ 1.f,1.f,1.f,1.f }
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

		if (Pos.y < 0.2f && ssz::Input::GetKey(ssz::eKeyCode::UP)) { Pos.y += 0.2f * (float)ssz::Time::DeltaTime(); }
		if (Pos.y > -0.2f && ssz::Input::GetKey(ssz::eKeyCode::DOWN)) { Pos.y -= 0.2f * (float)ssz::Time::DeltaTime(); }
		if (Pos.x < 0.2f && ssz::Input::GetKey(ssz::eKeyCode::RIGHT)) { Pos.x += 0.2f * (float)ssz::Time::DeltaTime(); }
		if (Pos.x > -0.2f && ssz::Input::GetKey(ssz::eKeyCode::LEFT)) { Pos.x -= 0.2f * (float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::SPACE)) { Pos.z = 0.02f; }

		SetPos(Pos);


		// 색상 변환

		Vector4 Color = GetColor();
		
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

		SetColor(Color);
	}

	void Player::LateUpdate()
	{
	}

	void Player::Render()
	{
		Circle::Render();
	}
}