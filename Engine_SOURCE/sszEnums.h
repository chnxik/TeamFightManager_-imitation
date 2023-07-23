#pragma once

namespace ssz::enums
{
	enum class eComponentType
	{
		None,
		Tranform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		UI,
		Camera,
		End,
	};

	enum class eLayerType
	{
		BackGround,
		BackGroundObj,
		Player,
		PlayerProjectile,
		Enemy,
		EnemyProjectile,
		UI,
		Cursor,
		Camera,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		Animation,
		End,
	};

	enum class eColliderType
	{
		Rect,
		Circle,
		Sphere,
		Cube,
		End,
	};
}
