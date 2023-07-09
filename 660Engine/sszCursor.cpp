#include "sszCursor.h"
#include "sszCursorScript.h"

#include "sszResources.h"
#include "sszShader.h"
#include "sszTexture.h"

#include "sszMaterial.h"
#include "sszMeshRenderer.h"


namespace ssz
{
	Cursor::Cursor()
	{
		Initialize();
	}

	Cursor::~Cursor()
	{
	}

	void Cursor::Initialize()
	{
		std::shared_ptr<Material>CursorMt = Resources::Find<Material>(L"CursorMt");
		if (CursorMt == nullptr)
		{
			// Mouse Cursor Tex
			Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");

			CursorMt = std::make_shared<Material>();
			CursorMt->SetMaterial(L"SpriteShader", L"CursorTex", eRenderingMode::Transparent);
			CursorMt = Resources::Insert(L"CursorMt", CursorMt);
		}

		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", L"CursorMt");
		AddComponent<CursorScript>()->Initialize();
	}

	void Cursor::Update()
	{
		GameObject::Update();
	}

	void Cursor::LateUpdate()
	{
		GameObject::LateUpdate();
	}

	void Cursor::Render()
	{
		GameObject::Render();
	}
}