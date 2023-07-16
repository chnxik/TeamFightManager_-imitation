#include "sszCursorScript.h"

#include "sszApplication.h"
#include "sszGameObject.h"

#include "sszInput.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszMaterial.h"
#include "sszCamera.h"
#include "sszCollider2D.h"

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
		CursorSize = GetOwner()->GetComponent<MeshRenderer>()->GetMaterial()->GetTexture()->GetTextureSize();
		
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
			// Get Mouse Pos
			Vector2 MousePos = Input::GetMousePos();
		
			// CursorSize로 위치 조정
			Vector3 FinalPos(MousePos.x + CursorSize.x, MousePos.y + CursorSize.y, 0.0f);
		
			RECT rect = {};
			GetClientRect(application.GetHwnd(), &rect);
			float width = (float)(rect.right - rect.left);
			float height = (float)(rect.bottom - rect.top);
		
			Viewport viewport;
			viewport.width = width;
			viewport.height = height;
			
			viewport.x = 0;
			viewport.y = 0;
			viewport.minDepth = 0.0f;
			viewport.maxDepth = 1.0f;
			
			FinalPos = viewport.Unproject(FinalPos, Camera::GetGpuProjectionMatrix(), Camera::GetGpuViewMatrix(), Matrix::Identity);
			
			GetOwner()->GetComponent<Transform>()->SetPosition(FinalPos);
		}
	}
}