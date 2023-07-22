#include "sszCursorScript.h"

#include "sszApplication.h"
#include "sszInput.h"

#include "sszGameObject.h"
#include "sszObject.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszCamera.h"
#include "sszCollider2D.h"

#include "sszResources.h"
#include "sszMaterial.h"

extern ssz::Application application;

namespace ssz
{
	CursorScript::CursorScript()
		: CursorSize{}
	{
	}

	CursorScript::~CursorScript()
	{
	}

	void CursorScript::Initialize()
	{
		GameObject* OwnerObj = GetOwner();

		// Set MeshRenderer
		Resources::Load<Texture>(L"CursorTex", L"..\\Resources\\useResource\\Cursor\\mouse_cursor.png");
		object::LoadMaterial(L"CursorMt", L"SpriteShader", L"CursorTex", eRenderingMode::Transparent);

		MeshRenderer* OwnerMeshRenderer = OwnerObj->AddComponent<MeshRenderer>();
		OwnerMeshRenderer->SetMeshRenderer(L"RectMesh", L"CursorMt");

		// Set CursorSize
		CursorSize = OwnerMeshRenderer->GetMaterial()->GetTexture()->GetTextureSize();
		
		// Set Collider
		OwnerObj->AddComponent<Collider2D>()->Initialize();

		Collider2D* CursorCol = GetOwner()->GetComponent<Collider2D>();
		if (CursorCol)
		{
			CursorCol->SetOffsetSize(Vector3(1.f - CursorSize.x, 1.f - CursorSize.y, 0.f));
			CursorCol->SetOffsetPos(Vector3(-CursorSize.x, CursorSize.y, 0.f) / 2.f);
		}

		CursorSize /= 2.f;
	}
	
	void CursorScript::LateUpdate()
	{
		{
			// Get Mouse Pos for DX
			Vector3 Pos = Input::GetMousePos4DX();

			// Cursor Size º¸Á¤
			Pos.x += CursorSize.x;
			Pos.y -= CursorSize.y;
			
			GetOwner()->GetComponent<Transform>()->SetPosition(Pos);
		}
	}
}