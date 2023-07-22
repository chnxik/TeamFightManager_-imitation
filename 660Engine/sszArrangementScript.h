#pragma once
#include <sszScript.h>

namespace ssz
{
	class UIObject;

	class ArrangementScript : public Script
	{
	public:
		ArrangementScript();
		virtual ~ArrangementScript();

		virtual void Initialize() override;
		virtual void Update() override;

		virtual void OnCollisionEnter(Collider2D* other);
		virtual void OnCollisionStay(Collider2D* other);
		virtual void OnCollisionExit(Collider2D* other);

	private:
		Vector3 ArrangePos;
		Vector3 ArrangeScale;
		Vector2 mPrevMousePos;
		float fradius;
		float fradiusx;
		float fradiusy;

		UIObject* OwnerUI;
	};
}