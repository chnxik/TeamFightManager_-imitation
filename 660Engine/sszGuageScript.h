#pragma once
#include "sszScript.h"

namespace ssz
{
    class GuageScript :
        public Script
    {
    public:
		enum eGuageType
		{
			INT,
			FLOAT,
			END,
		};

		GuageScript();
		virtual ~GuageScript();

		virtual void Update() override;
		virtual void LateUpdate() override;

		virtual void Binds() override;

		void SetValue(int Max, int* ValueAddress);
		void SetValue(float Max, float* ValueAddress);

	private:
		eGuageType mType;

		float mMax;
		void* mValue;
		
		float fRatio;
    };
}