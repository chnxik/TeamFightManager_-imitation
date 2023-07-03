#include "sszCursorScript.h"

#include "sszApplication.h"
#include "sszGameObject.h"

#include "sszInput.h"

#include "sszTransform.h"

extern ssz::Application application;

namespace ssz
{
	void CursorScript::Update()
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width = (float)(rect.right - rect.left);
		float height = (float)(rect.bottom - rect.top);

		// Get Mouse Pos
		Vector2 vMousePos = Input::GetMousePos();
		
		// winPos -> wolrdPos 변환 / camera 배율
		vMousePos.x = (vMousePos.x - width / 2.f) / 1000.f;
		vMousePos.y = -(vMousePos.y - height / 2.f) / 1000.f;

		// Cursor icon 보정
		Vector3 vCursorScale = GetOwner()->GetComponent<Transform>()->GetScale();
		vMousePos.x += vCursorScale.x / 2.f;
		vMousePos.y -= vCursorScale.y / 2.f;

		Vector3 FinalPos = GetOwner()->GetComponent<Transform>()->GetPosition();
		FinalPos.x = vMousePos.x;
		FinalPos.y = vMousePos.y;

		GetOwner()->GetComponent<Transform>()->SetPosition(FinalPos);
	}
}