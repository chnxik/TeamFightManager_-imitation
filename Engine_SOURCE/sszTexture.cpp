#include "sszTexture.h"
#include "sszGraphicDevice_Dx11.h"

namespace ssz::graphics
{
	Texture::Texture()
		: Resource(enums::eResourceType::Texture)
		, mImage{}
		, mTexture(nullptr)
		, mSRV(nullptr)
		, mDesc{}
		, width()
		, height()
	{
	}

	Texture::~Texture()
	{
	}

	bool Texture::Create(UINT width, UINT height, DXGI_FORMAT format, UINT bindFlag)
	{
		if (mTexture == nullptr)
		{
			mDesc.BindFlags = bindFlag;
			mDesc.Usage = D3D11_USAGE_DEFAULT;
			mDesc.CPUAccessFlags = 0;
			mDesc.Format = format;
			mDesc.Width = width;
			mDesc.Height = height;
			mDesc.ArraySize = 1;

			mDesc.SampleDesc.Count = 1;
			mDesc.SampleDesc.Quality = 0;

			mDesc.MipLevels = 0;
			mDesc.MiscFlags = 0;

			if (!GetDevice()->CreateTexture2D(&mDesc, nullptr, mTexture.GetAddressOf()))
				return false;
		}

		if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL)
		{
			if (!GetDevice()->CreateDepthStencilView(mTexture.Get(), nullptr, mDSV.GetAddressOf()))
				return false;
		}

		else if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_SHADER_RESOURCE)
		{
			D3D11_SHADER_RESOURCE_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = mDesc.Format;
			tSRVDesc.Texture2D.MipLevels = 1;
			tSRVDesc.Texture2D.MostDetailedMip = 0;
			tSRVDesc.ViewDimension = D3D11_SRV_DIMENSION::D3D11_SRV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateShaderResourceView(mTexture.Get(), &tSRVDesc, mSRV.GetAddressOf()))
				return false;
		}

		else if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_RENDER_TARGET)
		{
			D3D11_RENDER_TARGET_VIEW_DESC tSRVDesc = {};
			tSRVDesc.Format = mDesc.Format;
			tSRVDesc.Texture2D.MipSlice = 0;
			tSRVDesc.ViewDimension = D3D11_RTV_DIMENSION::D3D11_RTV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateRenderTargetView(mTexture.Get(), nullptr, mRTV.GetAddressOf()))
				return false;
		}

		else if (bindFlag & (UINT)D3D11_BIND_FLAG::D3D11_BIND_UNORDERED_ACCESS)
		{
			D3D11_UNORDERED_ACCESS_VIEW_DESC tUAVDesc = {};
			tUAVDesc.Format = mDesc.Format;
			tUAVDesc.Texture2D.MipSlice = 0;
			tUAVDesc.ViewDimension = D3D11_UAV_DIMENSION::D3D11_UAV_DIMENSION_TEXTURE2D;

			if (!GetDevice()->CreateUnorderedAccessView(mTexture.Get(), &tUAVDesc, mUAV.GetAddressOf()))
				return false;
		}


		return true;
	}


	HRESULT Texture::Load(const std::wstring& path)
	{
		wchar_t szExtension[50] = {};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, 50);

		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
				return S_FALSE;
		}
		else // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
				return S_FALSE;
		}

		CreateShaderResourceView
		(
			GetDevice()->GetID3D11Device()
			, mImage.GetImages()
			, mImage.GetImageCount()
			, mImage.GetMetadata()
			, mSRV.GetAddressOf()
		);
		
		mSRV->GetResource((ID3D11Resource**)mTexture.GetAddressOf());

		width = (float)mImage.GetMetadata().width;
		height = (float)mImage.GetMetadata().height;

		return S_OK;
	}

	void Texture::BindShader(eShaderStage stage, UINT startSlot)
	{
		GetDevice()->BindShaderResource(stage, startSlot, mSRV.GetAddressOf());
	}
	void Texture::Clear()
	{
		ID3D11ShaderResourceView* srv = nullptr;

		GetDevice()->BindShaderResource(eShaderStage::VS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::DS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::GS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::HS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::CS, 0, &srv);
		GetDevice()->BindShaderResource(eShaderStage::PS, 0, &srv);
	}
}