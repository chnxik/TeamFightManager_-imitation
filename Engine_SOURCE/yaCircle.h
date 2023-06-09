#pragma once
#include "yaGameObject.h"
#include "yaMath.h"
#include "yaConstantBuffer.h"

using namespace ya::math;

namespace ya
{
	class Circle : public GameObject
	{
	public:
		Circle();
		virtual ~Circle();

		virtual void Initialize();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render();

		void CreateCicle(Vector4 Pos, Vector4 Color);

		void SetPos(float x, float y) { mPos.x = x; mPos.y = y; }
		void SetPos(Vector4 Pos) { mPos = Pos; }
		void SetRadius(float fRadius) { mRadius = fRadius; mPos.z = mRadius; }
		void SetColor(float R, float G, float B) { mColor = Vector4(R,G,B,1.f); }

		Vector4 GetPos() { return mPos; }

	private:
		float	mRadius;
		Vector4 mPos;
		Vector4 mColor;
	};

}