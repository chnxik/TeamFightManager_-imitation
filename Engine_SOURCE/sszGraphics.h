#pragma once
#include <wrl.h>

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#include "sszEnums.h"
#include "sszMath.h"

#define CB_GETBINDSLOT(name) __CBUFFERBINDSLOT__##name##__
#define CBUFFER(name, slot) static const int CB_GETBINDSLOT(name) = slot; struct alignas(16) name

#define CBSLOT_TRANSFORM			0
#define CBSLOT_MASKING				1
#define CBSLOT_OVERLAPCNT			2
#define CBSLOT_ANIMATION2D			3
#define CBSLOT_CHAMP				4
#define CBSLOT_COLORFX				5
#define CBSLOT_GUAGE				6
// #define CBSLOT_PARTICLE				9


namespace ssz::graphics
{
	enum class eShaderStage
	{
		VS,
		HS,
		DS,
		GS,
		PS,
		CS,
		END,
	};

	enum class eCBType
	{
		Transform,
		Masking,
		Collider,
		Animator,
		Champ,
		ColorFX,
		Guage,
		Material,
		END,
	};

	enum class eSamplerType
	{
		Point,
		Anisotropic,
		END,
	};

	enum class eRSType
	{
		SolidBack,
		SolidFront,
		SolidNone,
		WireframeNone,
		END,
	};

	enum class eDSType
	{
		Less,
		Greater,
		NoWrite,
		None,
		END,
	};

	enum class eBSType
	{
		Default,
		AlphaBlend,
		OneOne,
		END,
	};

	enum class eRenderingMode
	{
		Opaque,
		CutOut,
		Transparent,
		End,
	};

	enum class eSRVType
	{
		None,
		End,
	};

	struct GpuBuffer
	{
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;
		D3D11_BUFFER_DESC desc;

		GpuBuffer()
			: buffer(nullptr)
			, desc{}
		{

		}
		virtual ~GpuBuffer() = default;
	};

	struct DebugMesh
	{
		enums::eColliderType type;
		math::Vector3 position;
		math::Vector3 rotation;
		math::Vector3 scale;

		float radius;
		float duration;
		float time;
		
		int OverlapCnt;
	};

	struct LightAttribute
	{
		math::Vector4		color;
		math::Vector4		position;
		math::Vector4		direction;

		enums::eLightType	type;
		float				radius;
		float				angle;
		int					pad;
	};
}