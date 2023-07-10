#pragma once
#include "sszEngine.h"
#include "sszGraphicDevice_Dx11.h"
#include "sszMesh.h"
#include "sszShader.h"
#include "sszConstantBuffer.h"
#include "sszCamera.h"

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
		Matrix mWorld;
		Matrix mView;
		Matrix mProjection;
	};

	CBUFFER(MaskingCB, CBSLOT_MASKING)
	{
		float Left;
		float Top;
		float Right;
		float Bottom;
	};
	
	extern ssz::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];

	extern Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[];
	extern Microsoft::WRL::ComPtr<ID3D11RasterizerState> rasterizerStates[];
	extern Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilStates[];
	extern Microsoft::WRL::ComPtr<ID3D11BlendState> blendStates[];

	extern std::vector<ssz::Camera*> cameras;
	extern std::vector<DebugMesh> debugMeshs;

	void Initialize();
	void Render();
	void Release();

	void PushDebugMeshAttribute(DebugMesh& mesh);
}
