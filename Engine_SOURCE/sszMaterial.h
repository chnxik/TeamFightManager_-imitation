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
		void Clear();

		void SetShader(std::shared_ptr<Shader> shader) { mShader = shader; }
		void SetShader(const std::wstring shaderkey);
		void SetTexture(std::shared_ptr<Texture> texture) { mTexture = texture; }
		void SetTexture(const std::wstring texturekey);
		void SetMaterial(std::shared_ptr<Shader> shader, std::shared_ptr<Texture> texture) { mShader = shader; mTexture = texture;
		}
		void SetMaterial(const std::wstring shaderkey, const std::wstring texturekey, eRenderingMode renderingmode);
		void SetRenderingMode(eRenderingMode mode) { mMode = mode; }
		eRenderingMode GetRenderingMode() { return mMode; }

		std::shared_ptr<Texture> GetTexture() 
		{ 
			if (mTexture != nullptr)
				return mTexture;
			else
				return nullptr;
		}

	private:
		std::shared_ptr<Shader> mShader;
		std::shared_ptr<Texture> mTexture;

		eRenderingMode mMode;
	};
} 