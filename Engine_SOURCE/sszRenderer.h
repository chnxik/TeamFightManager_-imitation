#pragma once
#include "sszEngine.h"
#include "sszGraphicDevice_Dx11.h"
#include "sszMesh.h"
#include "sszShader.h"
#include "sszConstantBuffer.h"

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
	
	extern Vertex vertexes[];
	extern ssz::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END];

	void Initialize();
	void Release();
}
