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
		Enemy,
		PlayerInteraction,
		EnemyInteraction,
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
		ComputeShader,
		File, // 삭제예정
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
