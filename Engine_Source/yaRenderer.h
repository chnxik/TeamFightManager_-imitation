#pragma once
#include "660Engine.h"
#include "yaGraphicDevice_Dx11.h"

using namespace ya::math;

namespace ya::renderer
{
	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	Vertex vertexes[];
	extern ID3D11InputLayout* triangleLayout;
	extern ID3D11Buffer* triangleBuffer;
	extern ID3DBlob* errorBlob;
	extern ID3DBlob* triangleVSBlob;
	extern ID3D11VertexShader* triangleVSShader;
	extern ID3DBlob* trianglePSBlob;
	extern ID3D11PixelShader* trianglePSShader;

	void Initialize();
}
