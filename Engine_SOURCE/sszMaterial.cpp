#include "sszMaterial.h"
#include "sszResources.h"


namespace ssz::graphics
{
    Material::Material()
        : Resource(ssz::enums::eResourceType::Material)
        , mShader(nullptr)
        , mTexture(nullptr)
        , mMode(eRenderingMode::Opaque)
    {
    }

    Material::~Material()
    {
    }

    HRESULT Material::Load(const std::wstring& path)
    {
        return E_NOTIMPL;
    }

    void Material::Binds()
    {
        if (mTexture)
            mTexture->BindShader(eShaderStage::PS, 0);

        if(mShader)
            mShader->Binds();
    }
    void Material::Clear()
    {
        mTexture->Clear();
    }
    void Material::SetShader(const std::wstring shaderkey)
    {
        mShader = ssz::Resources::Find<Shader>(shaderkey);
        assert(mShader != nullptr);
    }
    void Material::SetTexture(const std::wstring texturekey)
    {
        ssz::Resources::Find<Texture>(texturekey);
        assert(mShader != nullptr);
    }
    void Material::SetMaterial(const std::wstring shaderkey, const std::wstring texturekey, eRenderingMode renderingmode)
    {
        mShader = ssz::Resources::Find<Shader>(shaderkey);
        assert(mShader != nullptr);

        mTexture = ssz::Resources::Find<Texture>(texturekey);
        assert(mTexture != nullptr);

        mMode = renderingmode;
    }
}