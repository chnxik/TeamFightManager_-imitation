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
		MapSource,
		Tile,
		Player,
		Monster,
		UI,
		Camera,
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
