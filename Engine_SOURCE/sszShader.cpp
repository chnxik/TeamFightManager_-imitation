#include "sszShader.h"
#include "sszRenderer.h"

namespace ssz
{
    Shader::Shader()
        : Resource(enums::eResourceType::Shader)
        , mInputLayout(nullptr)
        , mTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST)
        , mRSType(eRSType::SolidBack)
        , mDSType(eDSType::Less)
        , mBSType(eBSType::AlphaBlend)
    {
    }

    Shader::~Shader()
    {
        mInputLayout->Release();
    }

    HRESULT ssz::Shader::Load(const std::wstring& path)
    {
        return E_NOTIMPL;
    }

    bool ssz::Shader::Create(const eShaderStage stage
        , const std::wstring& fileName
        , const std::string& funcName)
    {
        std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
        shaderPath += L"\\shader_SOURCE\\";

        std::filesystem::path fullPath(shaderPath.c_str());
        fullPath += fileName;

        ID3DBlob* errorBlob = nullptr;

        switch (stage)
        {
        case eShaderStage::VS:
            GetDevice()->CompileFromfile(fullPath, funcName, "vs_5_0", mVSBlob.GetAddressOf());
            GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer(), mVSBlob->GetBufferSize(), mVS.GetAddressOf());
            break;
        case eShaderStage::HS:
            break;
        case eShaderStage::DS:
            break;
        case eShaderStage::GS:
            break;
        case eShaderStage::PS:
            GetDevice()->CompileFromfile(fullPath, funcName, "ps_5_0", mPSBlob.GetAddressOf());
            GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer(), mPSBlob->GetBufferSize(), mPS.GetAddressOf());
            break;
        case eShaderStage::CS:
            break;
        default:
            break;
        }

        return true;
    }

    void ssz::Shader::Binds()
    {
        GetDevice()->BindPrimitiveTopology(mTopology);
        GetDevice()->BindInputLayout(mInputLayout);

        GetDevice()->BindVertexShader(mVS.Get());
        GetDevice()->BindPixelShader(mPS.Get());

        Microsoft::WRL::ComPtr<ID3D11RasterizerState> rsState = renderer::rasterizerStates[(UINT)mRSType];
        // Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState = renderer::depthStencilStates[(UINT)mDSType]; // renderer에서 작업을 해주고있음.
        Microsoft::WRL::ComPtr<ID3D11BlendState> bsState = renderer::blendStates[(UINT)mBSType];

        GetDevice()->BindRasterizerState(rsState.Get());
        // GetDevice()->BindDepthStencilState(dsState.Get());
        GetDevice()->BindBlendState(bsState.Get());

    }
}