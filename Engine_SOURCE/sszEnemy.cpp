#include "sszEnemy.h"
#include "sszTime.h"
#include "sszInput.h"

namespace ssz
{
	ssz::Enemy::Enemy()
		: mMagnet(eMagnet::OFF)
		, mTarget(nullptr)
	{
	}

	ssz::Enemy::~Enemy()
	{
	}

	void ssz::Enemy::Initialize()
	{
	}

	void ssz::Enemy::Update()
	{
		Vector4 Pos = GetPos();
		
		if (mMagnet == eMagnet::OFF)
		{
			if (ssz::Input::GetKey(ssz::eKeyCode::UP)) { Pos.y += 0.5f * (float)ssz::Time::DeltaTime(); }
			if (ssz::Input::GetKey(ssz::eKeyCode::DOWN)) { Pos.y -= 0.5f * (float)ssz::Time::DeltaTime(); }
			if (ssz::Input::GetKey(ssz::eKeyCode::RIGHT)) { Pos.x += 0.5f * (float)ssz::Time::DeltaTime(); }
			if (ssz::Input::GetKey(ssz::eKeyCode::LEFT)) { Pos.x -= 0.5f * (float)ssz::Time::DeltaTime(); }
		}
		else if ( mMagnet == eMagnet::ON)
		{
			Vector4 TargetPos = mTarget->GetPos();
			float length = 0.f; // 타겟까지 거리
			Vector2 Dir = {TargetPos.x - Pos.x, TargetPos.y - Pos.y}; // 타겟 방향

			// 타겟 - 본인 위치
			length = sqrt((TargetPos.x - Pos.x) * (TargetPos.x - Pos.x) + (TargetPos.y - Pos.y) * (TargetPos.y - Pos.y));

			Dir /= length;

			Pos.x += Dir.x * 1.f * (float)ssz::Time::DeltaTime();
			Pos.y += Dir.y * 1.f * (float)ssz::Time::DeltaTime();
		}

		SetPos(Pos);
	}

	void ssz::Enemy::LateUpdate()
	{
	}

	void ssz::Enemy::Render()
	{
		Circle::Render();
	}
	bool Enemy::IsMagnet()
	{
		switch (mMagnet)
		{
		case ssz::Enemy::ON:
			return true;
			break;
		case ssz::Enemy::OFF:
			return false;
			break;
		default:
			return false;
			break;
		}
	}
	void Enemy::SetMagnet(Circle* Target)
	{
		mMagnet = eMagnet::ON;
		mTarget = Target;
	}
}