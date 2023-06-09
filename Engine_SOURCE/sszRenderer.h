#pragma once
#include "sszEngine.h"
#include "sszGraphicDevice_Dx11.h"
#include "sszMesh.h"
#include "sszShader.h"
#include "sszConstantBuffer.h"

using namespace ssz::math;

namespace renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};
	
	extern Vertex vertexes[];
	extern ssz::Mesh* mesh;
	extern ssz::Shader* shader;
	extern ssz::graphics::ConstantBuffer* TransformConstantBuffer;
	extern ssz::graphics::ConstantBuffer* ColorConstantBuffer;

	ssz::graphics::ConstantBuffer* GetConstantBuffer(eCBType CBType);

	void Initialize();
	void Release();
}
