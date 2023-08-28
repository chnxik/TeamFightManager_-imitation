#pragma once
#include "sszEngine.h"
#include "sszGraphicDevice_Dx11.h"
#include "sszMesh.h"
#include "sszShader.h"
#include "sszConstantBuffer.h"
#include "sszCamera.h"
#include "sszLight.h"

using namespace ssz::math;
using namespace ssz::graphics;

namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	CBUFFER(TransformCB, CBSLOT_TRANSFORM)
	{
		Matrix	mWorld;
		Matrix	mView;
		Matrix	mProjection;
		float	mDir;
	};

	CBUFFER(MaskingCB, CBSLOT_MASKING)
	{
		float Left;
		float Top;
		float Right;
		float Bottom;
	};

	CBUFFER(ColliderCB, CBSLOT_OVERLAPCNT)
	{
		int OverlapCnt;
	};

	CBUFFER(AnimatorCB, CBSLOT_ANIMATION2D)
	{
		Vector2 spriteLeftTop;
		Vector2 spriteSize;
		Vector2 spriteOffset;
		Vector2 atlasSize;
	};

	CBUFFER(ChampCB, CBSLOT_CHAMP)
	{
		float DamagedTime;
	};
	
	extern ConstantBuffer* constantBuffer[(UINT)eCBType::END];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<ssz::Light*> lights;
	extern std::vector<ssz::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void Render();
	void Release();
	
	void BindLights();
	void CameraClear();

	void PushDebugMeshAttribute(DebugMesh& mesh);
}
