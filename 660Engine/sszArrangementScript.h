#pragma once
#include <sszScript.h>

namespace ssz
{
	class ArrangementScript : public Script
	{
	public:
		ArrangementScript();
		virtual ~ArrangementScript();

		virtual void Initialize() override;
		virtual void Update() override;

		void SetDefault();

	private:
		Vector3 ArrangePos;
		Vector3 ArrangeScale;
		float fradius;
		float fradiusx;
		float fradiusy;
	};
}