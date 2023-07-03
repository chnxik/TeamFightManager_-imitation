#pragma once

namespace ssz::enums
{
	enum class eComponentType
	{
		None,
		Tranform,
		Mesh,
		Particle,
		MeshRenderer,
		Script,
		Camera,
		End,
	};

	enum class eLayerType
	{
		BackGround,
		Player,
		Monster,
		UI,
		Cursor,
		End,
	};

	enum class eResourceType
	{
		Texture,
		Shader,
		Material,
		Mesh,
		End,
	};
}
