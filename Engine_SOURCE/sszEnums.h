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
		Light,
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
		Light,
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
		File,
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

	enum class eLightType
	{
		Directional,
		Point,
		Spot,
		End
	};
}
