#include "sszMeshRenderer.h"
#include "sszGameObject.h"
#include "sszTransform.h"
#include "sszMasking.h"
#include "sszRenderer.h"

namespace ssz
{
	MeshRenderer::MeshRenderer()
		: Component(eComponentType::MeshRenderer)
	{
	}

	MeshRenderer::~MeshRenderer()
	{
	}

	void MeshRenderer::Initialize()
	{
	}

	void MeshRenderer::Update()
	{
	}

	void MeshRenderer::LateUpdate()
	{
	}

	void MeshRenderer::Render()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		tr->BindConstantBuffer();

		Masking* ms = GetOwner()->GetComponent<Masking>();
		if (ms != nullptr)
		{
			ms->BindConstantBuffer();
		}

		mMesh->BindBuffer();
		mMaterial->Binds();
		mMesh->Render();

		mMaterial->Clear();
	}
}