#include "yaRenderer.h"
#include "yaTime.h"
#include "yaInput.h"

namespace ya::renderer
{
	Vertex vertexes[3] = {};
	Vector4 Pos = { 0.f,0.f,0.f,0.f };

	// Inpt Layout (정점 정보)
	ID3D11InputLayout* triangleLayout = nullptr;

	// Vertex Buffer
	ID3D11Buffer* VertexBuffer = nullptr;

	// Index Buffer
	ID3D11Buffer* IndexBuffer = nullptr;

	// Constant Buffer
	ID3D11Buffer* ConstantBuffer = nullptr;

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
		// Vertex Buffer
		D3D11_BUFFER_DESC VSDesc = { };
		VSDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		VSDesc.ByteWidth = sizeof(Vertex) * 3;
		VSDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		VSDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA VSData = {};
		VSData.pSysMem = vertexes;
		ya::graphics::GetDevice()->CreateBuffer(&VertexBuffer, &VSDesc, &VSData);

		// Index Buffer
		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		D3D11_BUFFER_DESC IBDesc = { };
		IBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DEFAULT;
		IBDesc.ByteWidth = sizeof(UINT) * (UINT)indexes.size();
		IBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		IBDesc.CPUAccessFlags = 0;
		
		D3D11_SUBRESOURCE_DATA IBData = {};
		IBData.pSysMem = indexes.data();
		ya::graphics::GetDevice()->CreateBuffer(&IndexBuffer, &IBDesc, &IBData);

		// Constant Buffer
		D3D11_BUFFER_DESC CBDesc = { };
		CBDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
		CBDesc.ByteWidth = sizeof(Vector4);
		CBDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		CBDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

		ya::graphics::GetDevice()->CreateBuffer(&ConstantBuffer, &CBDesc, nullptr);
	}

	void LoadShader()
	{
		ya::graphics::GetDevice()->CreateShader();
	}

	void Initialize()
	{
		// vertex 설정
		vertexes[0].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[1].pos = Vector3(0.0f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		SetupState();
		LoadBuffer();
		LoadShader();
	}

	void update()
	{
		if (ya::Input::GetKey(eKeyCode::UP))	{ Pos.y += 2.f *(float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(eKeyCode::DOWN))	{ Pos.y -= 2.f *(float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(eKeyCode::RIGHT)) { Pos.x += 2.f *(float)ya::Time::DeltaTime(); }
		if (ya::Input::GetKey(eKeyCode::LEFT))	{ Pos.x -= 2.f *(float)ya::Time::DeltaTime(); }
		
		ya::graphics::GetDevice()->SetConstantBuffer(ya::renderer::ConstantBuffer, &Pos, sizeof(Vector4));
		ya::graphics::GetDevice()->BindConstantBuffer(eShaderStage::VS, eCBT::Transform, ya::renderer::ConstantBuffer);
	}
}
