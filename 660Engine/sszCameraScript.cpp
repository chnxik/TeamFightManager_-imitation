#include "sszCameraScript.h"

#include "sszTime.h"
#include "sszInput.h"

#include "sszGameObject.h"

#include "sszTransform.h"

namespace ssz
{
	void CameraScript::Update()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetLocalPosition();

		if (Input::GetKey(eKeyCode::D)) { pos.x += 5.0f * (float)Time::DeltaTime(); }
		if (Input::GetKey(eKeyCode::A)) { pos.x -= 5.0f * (float)Time::DeltaTime(); }
		if (Input::GetKey(eKeyCode::W)) { pos.y += 5.0f * (float)Time::DeltaTime(); }
		if (Input::GetKey(eKeyCode::S)) { pos.y -= 5.0f * (float)Time::DeltaTime(); }
		if (Input::GetKey(eKeyCode::Q)) { pos.z += 5.0f * (float)Time::DeltaTime(); }
		if (Input::GetKey(eKeyCode::E)) { pos.z -= 5.0f * (float)Time::DeltaTime(); }

		tr->SetLocalPosition(pos);
	}
}