#include "sszCursor.h"
#include "CommonObjHeader.h"

#include "sszCursorScript.h"

namespace ssz 
{
	GameObject* Cursor::mCursor = nullptr;

	void Cursor::Initialize()
	{
		mCursor = new GameObject();
		Transform* tr = mCursor->GetComponent<Transform>();

		Vector3 Scale(32.f, 32.f, 1.f);
		Vector3 Pos(0.f, 0.f, 0.01f);

		tr->SetPosition(Pos);
		tr->SetScale(Scale);

		mCursor->SetName(L"Cursor");
		mCursor->AddComponent<CursorScript>();
	}

	void Cursor::RegistCursor(Scene* pActiveScene)
	{
		pActiveScene->AddGameObject(enums::eLayerType::Cursor, mCursor);
	}
}