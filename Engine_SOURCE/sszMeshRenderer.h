#pragma once
#include "sszComponent.h"
#include "sszMesh.h"
#include "sszShader.h"

namespace ssz
{
	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		~MeshRenderer();

		virtual void Initialize() override;
		virtual void Update() override;
		virtual void LateUpdate() override;
		virtual void Render() override;

	private:
		Mesh* mMesh;
		Shader* mShader;
	};

}