#include "sszRenderer.h"
#include "sszTime.h"
#include "sszInput.h"

namespace renderer
{
	Vertex vertexes[4] = {};
	ssz::Mesh* mesh = nullptr;
	ssz::Shader* shader = nullptr;
	ssz::graphics::ConstantBuffer* ConstantBuffer = nullptr;
	Vector4 Pos = { 0.f,0.f,0.f,0.f };

	void SetupState()
	{
		// InputLayout 정점 구조 정보를 넘겨준다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

		arrLayout[0].AlignedByteOffset = 0;
		arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
		arrLayout[0].InputSlot = 0;
		arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[0].SemanticName = "POSITION";
		arrLayout[0].SemanticIndex = 0;

		arrLayout[1].AlignedByteOffset = 12;
		arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		arrLayout[1].InputSlot = 0;
		arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[1].SemanticName = "COLOR";
		arrLayout[1].SemanticIndex = 0;

		ssz::graphics::GetDevice()->CreateInputLayout(arrLayout, 2
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());
	}

	void LoadBuffer()
	{
		// Mesh
		mesh = new ssz::Mesh();
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		
		indexes.push_back(2);
		indexes.push_back(1);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), indexes.size());

		// Constant Buffer
		ConstantBuffer = new ssz::graphics::ConstantBuffer(eCBType::Transform);
		ConstantBuffer->Create(sizeof(Vector4));
	}

	void LoadShader()
	{
		shader = new ssz::Shader();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
	}

	void Initialize()
	{
		// vertex 설정
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		vertexes[3].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		SetupState();
	}

	void Release()
	{
		delete mesh;
		delete shader;
		delete ConstantBuffer;
	}

	void update()
	{
		if (ssz::Input::GetKey(ssz::eKeyCode::UP))	{ Pos.y += 2.f *(float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::DOWN))	{ Pos.y -= 2.f *(float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::RIGHT)) { Pos.x += 2.f *(float)ssz::Time::DeltaTime(); }
		if (ssz::Input::GetKey(ssz::eKeyCode::LEFT))	{ Pos.x -= 2.f *(float)ssz::Time::DeltaTime(); }
		
		ConstantBuffer->SetData(&Pos);
		ConstantBuffer->Bind(eShaderStage::VS);
	}
}