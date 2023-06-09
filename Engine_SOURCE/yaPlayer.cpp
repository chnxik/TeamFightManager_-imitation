#include "yaPlayer.h"
#include "yaTime.h"
#include "yaInput.h"
#include "yaRenderer.h"

namespace ya
{
	Player::Player()
	{
	}

	Player::~Player()
	{
	}

	void Player::Initialize()
	{
		GameObject::Initialize();
	}

	void Player::Update()
	{
		Vector4 Pos = GetPos();

		if (ya::Input::GetKey(ya::eKeyCode::UP)) { Pos.y += 1.f * (float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(ya::eKeyCode::DOWN)) { Pos.y -= 1.f * (float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(ya::eKeyCode::RIGHT)) { Pos.x += 1.f * (float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(ya::eKeyCode::LEFT)) { Pos.x -= 1.f * (float)ya::Time::DeltaTime(); }

		SetPos(Pos);
	}

	void Player::LateUpdate()
	{
	}

	void Player::Render()
	{
		Circle::Render();
	}
}