#pragma once
#include "sszResource.h"
#include "sszShader.h"
#include "sszTexture.h"

namespace ssz::graphics
{
	class Material : public Resource
	{
	public:
		Material();
		~Material();

		virtual HRESULT Load(const std::wstring& path) override;

		void Binds();

		void SetShader(Shader* shader) { mShader = shader; }
		void SetTexture(Texture* texture) { mTexture = texture; }

	private:
		Shader* mShader;
		Texture* mTexture;
	};
}