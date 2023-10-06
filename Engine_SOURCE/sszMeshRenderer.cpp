#include "sszMeshRenderer.h"
#include "sszGameObject.h"
#include "sszTransform.h"
#include "sszRenderer.h"

#include "sszResources.h"
#include "sszMesh.h"
#include "sszMaterial.h"

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
		for (Component* Comp : GetOwner()->GetComponents())
		{
			Comp->Binds();
		}

		for (Script* Script : GetOwner()->GetScripts())
		{
			Script->Binds();
		}

		mMesh->BindBuffer();
		mMaterial->Binds();
		mMesh->Render();

		for (Component* Comp : GetOwner()->GetComponents())
		{
			Comp->BindsClear();
		}

		for (Script* Script : GetOwner()->GetScripts())
		{
			Script->BindsClear();
		}

		mMaterial->Clear();
	}
	
	void MeshRenderer::Render(Component* comp)
	{
		comp->Binds();

		mMesh->BindBuffer();
		mMaterial->Binds();
		mMesh->Render();

		mMaterial->Clear();
	}

	void MeshRenderer::SetMaterial(const std::wstring& key)
	{
		std::shared_ptr<Material> NewMaterial = Resources::Find<Material>(key);
		assert(NewMaterial != nullptr);

		mMaterial = NewMaterial;
	}

	void MeshRenderer::SetMeshRenderer(const std::wstring MeshKey, const std::wstring MaterialKey)
	{
		mMesh = ssz::Resources::Find<Mesh>(MeshKey);
		assert(mMesh != nullptr);

		mMaterial = ssz::Resources::Find<Material>(MaterialKey);
		assert(mMaterial != nullptr);
	}
}