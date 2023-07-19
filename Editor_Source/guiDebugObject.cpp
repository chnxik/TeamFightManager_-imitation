#include "guiDebugObject.h"
#include "..\Engine_SOURCE\sszEnums.h"
#include "..\Engine_SOURCE\sszMeshRenderer.h"

namespace gui
{
	DebugObject::DebugObject(ssz::enums::eColliderType eType)
		: mType(eType)
	{
		switch (eType)
		{
		case ssz::enums::eColliderType::Rect:
			AddComponent<ssz::MeshRenderer>()->SetMeshRenderer(L"DebugRect", L"DebugMaterial");
			break;
		case ssz::enums::eColliderType::Circle:
			AddComponent<ssz::MeshRenderer>()->SetMeshRenderer(L"DebugCircle", L"DebugMaterial");
			break;
		case ssz::enums::eColliderType::Sphere:
			break;
		case ssz::enums::eColliderType::Cube:
			break;
		case ssz::enums::eColliderType::End:
			break;
		}
	}
	DebugObject::~DebugObject()
	{
	}
	void DebugObject::Initialize()
	{
	}
	void DebugObject::Update()
	{
	}
	void DebugObject::LateUpdate()
	{
		GameObject::LateUpdate();
	}
	void DebugObject::Render()
	{
		GameObject::Render();
	}
}