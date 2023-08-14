#include "sszCursor.h"
#include "CommonObjHeader.h"

#include "sszCursorScript.h"

namespace ssz 
{
	Cursor::Cursor()
	{
	}

	Cursor::~Cursor()
	{
	}
	
	void Cursor::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetPosition(Vector3(0.f, 0.f, 0.01f));
		tr->SetScale(Vector3(32.f, 32.f, 1.f));

		SetName(L"Cursor");

		AddComponent<CursorScript>();
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