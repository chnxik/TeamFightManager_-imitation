#pragma once

namespace ssz::enums
{
	enum class eComponentType
	{
		None,
		Rigidbody,
		Tranform,
		Mesh,
		Collider2D,
		Particle,
		MeshRenderer,
		Animator,
		Script,
		Light,
		Text,
		AudioListener,
		AudioSource,
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
		Effect,
		Light,
		UI,
		Cursor,
		SoundSource,
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
		AudioClip,
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
