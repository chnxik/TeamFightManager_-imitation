#include "yaRenderer.h"


namespace ya::renderer
{
	Vertex vertexes[44] = {};
	UINT Index[102] = {};
	
	int circlePoint = 25; // 원 다각형 갯수

	// Inpt Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* FigureBuffer = nullptr;

	// Index Buffer
	ID3D11Buffer* IndexBuffer = nullptr;

	// error Blob
	ID3DBlob* errorBlob = nullptr;

	// Vertex Shader code -> Binary Code
	ID3DBlob* triangleVSBlob = nullptr;

	// Vertex Shader
	ID3D11VertexShader* triangleVSShader = nullptr;
	
	// Pixel Shader code -> Binary Code
	ID3DBlob* trianglePSBlob = nullptr;

	// Pixel Shader
	ID3D11PixelShader* trianglePSShader = nullptr;

	void SetupState()
	{

	}

	void LoadBuffer()
	{
		D3D11_BUFFER_DESC triangleDesc = { };
		triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		triangleDesc.ByteWidth = sizeof(Vertex) * 44;
		triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA triangleData = {};
		triangleData.pSysMem = vertexes;
		ya::graphics::GetDevice()->CreateBuffer(&FigureBuffer, &triangleDesc, &triangleData);

		// Index Buffer
		D3D11_BUFFER_DESC Indexdesc = { };
		Indexdesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		Indexdesc.ByteWidth = sizeof(UINT) * 102;
		Indexdesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		Indexdesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
			
		D3D11_SUBRESOURCE_DATA IndexData = {};
		IndexData.pSysMem = Index;
		ya::graphics::GetDevice()->CreateBuffer(&IndexBuffer, &Indexdesc, &IndexData);

	}

	void LoadShader()
	{
		ya::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		// 사각형 vertex 설정
		vertexes[0].pos = Vector3(-0.75f, 0.75f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[1].pos = Vector3(-0.25f, 0.75f, 0.0f);
		vertexes[1].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.75f, 0.25f, 0.0f);
		vertexes[2].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.25f, 0.25f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		
		// 사각형 index 설정
		Index[0] = 0;
		Index[1] = 1;
		Index[2] = 2;
		Index[3] = 2;
		Index[4] = 1;
		Index[5] = 3;
		
		// 원 vertex 설정
		vertexes[4].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[4].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

		for (int i = 0; i < circlePoint; ++i)
		{
			float x = 0.0f;
			float y = 0.0f;
			float r = 0.25f;
			float degree = (360.f / (float)circlePoint) * i;
			float radian = (3.141592f / 180.f) * degree;

			x = 0.5f + (r * cosf(radian));
			y = 0.5f + (r * sinf(radian));

			vertexes[i + 5].pos = Vector3(x, y, 0.0f);
			vertexes[i + 5].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		}
		
		// 원 index 설정

		for (int i = 0; i < circlePoint; ++i)
		{
			int circleIndexStart = 4;
			Index[6 + (i * 3)] = circleIndexStart; // 중점
		
			if (circlePoint - 1 == i)
			{
				Index[7 + (i * 3)] = circleIndexStart + 1;
				Index[8 + (i * 3)] = circleIndexStart + i + 1;
			}
			else
			{
				Index[7 + (i * 3)] = circleIndexStart + i + 2;
				Index[8 + (i * 3)] = circleIndexStart + i + 1;
			}
		}

		// 별 vertex 설정
		vertexes[32].pos = Vector3(-0.70f, -0.63f, 0.0f);
		vertexes[32].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[33].pos = Vector3(-0.5f, -0.25f, 0.0f);
		vertexes[33].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[34].pos = Vector3(-0.30f, -0.63f, 0.0f);
		vertexes[34].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[35].pos = Vector3(-0.70f, -0.37f, 0.0f);
		vertexes[35].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[36].pos = Vector3(-0.30f, -0.37f, 0.0f);
		vertexes[36].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		vertexes[37].pos = Vector3(-0.5f, -0.75f, 0.0f);
		vertexes[37].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

		// 별 index 설정

		Index[81] = 32;
		Index[82] = 33;
		Index[83] = 34;
		Index[84] = 35;
		Index[85] = 36;
		Index[86] = 37;

		// 5각형 vertex 설정

		vertexes[38].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[38].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

		for (int i = 0; i < 5; ++i)
		{
			float x = 0.0f, y = 0.0f, r = 0.25f;
			float degree = (360.f / (float)5) * i;
			float radian = (3.141592f / 180.f) * degree;
			
			x = 0.5f + (r * cosf(radian));
			y = -0.5f + (r * sinf(radian));

			vertexes[i + 39].pos = Vector3(x, y, 0.0f);
			vertexes[i + 39].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		}

		// 5각형 index 설정

		for (int i = 0; i < 5; ++i)
		{
			int IndexStart = 38;
			Index[87 + (i * 3)] = IndexStart; // 중점

			if (5 - 1 == i)
			{
				Index[88 + (i * 3)] = IndexStart + 1;
				Index[89 + (i * 3)] = IndexStart + i + 1;
			}
			else
			{
				Index[88 + (i * 3)] = IndexStart + i + 2;
				Index[89 + (i * 3)] = IndexStart + i + 1;
			}
		}


		SetupState();
		LoadBuffer();
		LoadShader();
	}
}
