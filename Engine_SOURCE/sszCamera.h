#pragma once
#include "sszComponent.h"
#include "sszGraphics.h"

namespace ssz
{
	class Camera : public Component
	{
	public:
		enum class eProjectionType
		{
			Perspective,
			OrthoGraphic,
			None,
		};

		static Matrix GetViewMatrix() {	return mView; }
		static Matrix GetProjectionMatrix() { return mProjection; }

		Camera();
		~Camera();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

		bool CreateViewMatrix();
		bool CreateProjectionMatrix(eProjectionType type);


	private:
		static Matrix mView;
		static Matrix mProjection;

		eProjectionType mType;
		float mAspectRatio;
		float mNear;
		float mFar;
		float mSize;
	};
}