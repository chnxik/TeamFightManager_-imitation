#include "sszRenderer.h"
#include "sszResources.h"
#include "sszTexture.h"
#include "sszMaterial.h"

namespace renderer
{
	using namespace ssz;
	using namespace ssz::graphics;

	Vertex vertexes[4] = {};
	ssz::graphics::ConstantBuffer* constantBuffer[(UINT)eCBType::END] = {};
	Microsoft::WRL::ComPtr<ID3D11SamplerState> samplerState[(UINT)eSamplerType::END] = {};

	void SetupState()
	{
		// InputLayout 정점 구조 정보를 넘겨준다.
		D3D11_INPUT_ELEMENT_DESC arrLayout[3] = {};

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

		arrLayout[2].AlignedByteOffset = 28;
		arrLayout[2].Format = DXGI_FORMAT_R32G32_FLOAT;
		arrLayout[2].InputSlot = 0;
		arrLayout[2].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
		arrLayout[2].SemanticName = "TEXCOORD";
		arrLayout[2].SemanticIndex = 0;

		std::shared_ptr<Shader> shader = ssz::Resources::Find<Shader>(L"TriangleShader");
		ssz::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		shader = ssz::Resources::Find<Shader>(L"SpriteShader");
		ssz::graphics::GetDevice()->CreateInputLayout(arrLayout, 3
			, shader->GetVSCode()
			, shader->GetInputLayoutAddressOf());

		// Sampler State
		D3D11_SAMPLER_DESC desc = {};
		desc.AddressU = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressV = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.AddressW = D3D11_TEXTURE_ADDRESS_MODE::D3D11_TEXTURE_ADDRESS_WRAP;
		desc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Point].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 0, samplerState[(UINT)eSamplerType::Point].GetAddressOf());

		desc.Filter = D3D11_FILTER_ANISOTROPIC;
		GetDevice()->CreateSampler(&desc, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
		GetDevice()->BindSampler(eShaderStage::PS, 1, samplerState[(UINT)eSamplerType::Anisotropic].GetAddressOf());
	}

	void LoadBuffer()
	{
		// Mesh
		std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
		Resources::Insert(L"RectMesh", mesh);
		
		mesh->CreateVertexBuffer(vertexes, 4);

		std::vector<UINT> indexes = {};
		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		
		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);
		mesh->CreateIndexBuffer(indexes.data(), (UINT)indexes.size());

		// Constant Buffer
		constantBuffer[(UINT)eCBType::Transform] = new ConstantBuffer(eCBType::Transform);
		constantBuffer[(UINT)eCBType::Transform]->Create(sizeof(TransformCB));
	}

	void LoadShader()
	{

		std::shared_ptr<Shader> shader = std::make_shared<Shader>();
		shader->Create(eShaderStage::VS, L"TriangleVS.hlsl", "main");
		shader->Create(eShaderStage::PS, L"TrianglePS.hlsl", "main");
		ssz::Resources::Insert(L"TriangleShader", shader);

		std::shared_ptr<Shader> spriteshader = std::make_shared<Shader>();
		spriteshader->Create(eShaderStage::VS, L"SpriteVS.hlsl", "main");
		spriteshader->Create(eShaderStage::PS, L"SpritePS.hlsl", "main");
		ssz::Resources::Insert(L"SpriteShader", spriteshader);
	}

	void LoadMaterial()
	{
		// Matrial에 사용할 Shader 호출
		std::shared_ptr<Shader> spriteshader = ssz::Resources::Find<Shader>(L"SpriteShader");

		// [Load Material]
		// Load Texture

		std::shared_ptr<Texture> TitleBg
			= Resources::Load<Texture>(L"TitleBg", L"..\\Resources\\Texture\\Title\\Bg\\Spr_Thumnnail.png");

		std::shared_ptr<Texture> Prlg01Bg
		 	= Resources::Load<Texture>(L"Prlg01Bg", L"..\\Resources\\Texture\\Prlg\\01\\Bg\\Spr_PRLG_Forest_BG_Sky.png");

		std::shared_ptr<Texture> Prlg02Bg
			= Resources::Load<Texture>(L"Prlg02Bg", L"..\\Resources\\Texture\\Prlg\\02\\Bg\\Spr_PRLG_Forest_BG_InsideShack.png");

		std::shared_ptr<Texture> Prlg03Bg
		 	= Resources::Load<Texture>(L"Prlg03Bg", L"..\\Resources\\Texture\\Prlg\\03\\Bg\\Spr_PRLG_BG_Sky.png");

		std::shared_ptr<Material> TitleBgMaterial = std::make_shared<Material>();
		TitleBgMaterial->SetShader(spriteshader);
		TitleBgMaterial->SetTexture(TitleBg);
		Resources::Insert(L"TitleBgMaterial", TitleBgMaterial);

		std::shared_ptr<Material> Prlg01BgMaterial = std::make_shared<Material>();
		Prlg01BgMaterial->SetShader(spriteshader);
		Prlg01BgMaterial->SetTexture(Prlg01Bg);
		Resources::Insert(L"Prlg01BgMaterial", Prlg01BgMaterial);

		std::shared_ptr<Material> Prlg02BgMaterial = std::make_shared<Material>();
		Prlg02BgMaterial->SetShader(spriteshader);
		Prlg02BgMaterial->SetTexture(Prlg02Bg);
		Resources::Insert(L"Prlg02BgMaterial", Prlg02BgMaterial);

		std::shared_ptr<Material> Prlg03BgMaterial = std::make_shared<Material>();
		Prlg03BgMaterial->SetShader(spriteshader);
		Prlg03BgMaterial->SetTexture(Prlg03Bg);
		Resources::Insert(L"Prlg03BgMaterial", Prlg03BgMaterial);
	}

	void Initialize()
	{
		// vertex 설정
		vertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
		vertexes[0].uv = Vector2(0.0f, 0.0f);

		vertexes[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
		vertexes[1].uv = Vector2(1.0f, 0.0f);

		vertexes[2].pos = Vector3(0.5f, -0.5f, 0.0f);
		vertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
		vertexes[2].uv = Vector2(1.0f, 1.0f);

		vertexes[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexes[3].color = Vector4(1.0f, 1.0f, 1.0f, 1.0f);
		vertexes[3].uv = Vector2(0.0f, 1.0f);

		LoadBuffer();
		LoadShader();
		LoadMaterial();
		SetupState();
	}

	void Release()
	{
		for (ConstantBuffer* buff : constantBuffer)
		{
			if (buff == nullptr)
				continue;

			delete buff;
			buff = nullptr;
		}
	}
}