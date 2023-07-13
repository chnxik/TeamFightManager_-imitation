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
		Script,
		Camera,
		Panel,
		End,
	};

	enum class eLayerType
	{
		BackGround,
		BackGroundObj,
		Player,
		UI,
		Cursor,
		End = 16,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
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
