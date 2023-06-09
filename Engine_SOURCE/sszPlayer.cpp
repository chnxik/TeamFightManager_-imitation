#include "sszPlayer.h"
#include "sszTime.h"
#include "sszInput.h"
#include "sszRenderer.h"

namespace ssz
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

		if (ssz::Input::GetKey(ssz::eKeyCode::UP)) { Pos.y += 1.f * (float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::DOWN)) { Pos.y -= 1.f * (float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::RIGHT)) { Pos.x += 1.f * (float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::LEFT)) { Pos.x -= 1.f * (float)ssz::Time::DeltaTime(); }

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