#include "sszMeshRenderer.h"
#include "sszGameObject.h"
#include "sszTransform.h"
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

		renderer::mesh->BindBuffer();
		renderer::shader->Binds();
		GetDevice()->DrawIndexed(renderer::mesh->GetIndexCount(), 0, 0);
	}
}