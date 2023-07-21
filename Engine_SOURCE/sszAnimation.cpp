#include "sszAnimation.h"
#include "sszTime.h"
#include "sszAnimator.h"
#include "sszRenderer.h"
#include "sszConstantBuffer.h"

namespace ssz
{
	Animation::Animation()
		: Resource(enums::eResourceType::Animation)
		, mAtlas(nullptr)
		, mAnimator(nullptr)
		, mSprites{}
		, mIndex(-1)
		, mTime(0.f)
		, mbComplete(false)
	{
	}

	Animation::~Animation()
	{
	}
	
	void Animation::Update()
	{
		if (mbComplete)
			return;

		mTime += (float)Time::DeltaTime();

		if (mSprites[mIndex].duration <= mTime)
		{
			mTime = mTime - mSprites[mIndex].duration;
			mIndex++;

			if (mSprites.size() <= mIndex)
			{
				mIndex = (UINT)mSprites.size() - 1;
				mbComplete = true;
			}
		}
	}
	
	void Animation::LateUpdate()
	{
	}
	
	void Animation::Render()
	{
	}
	
	void Animation::Create(std::wstring name, std::shared_ptr<graphics::Texture> atlas, Vector2 leftTop, Vector2 size, UINT columnLength, Vector2 offset, float duration)
	{
		SetKey(name);
		mAtlas = atlas;

		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();
		float ratio = 32.f;

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size.x = size.x / width;
			sprite.size.y = size.y / height;
			sprite.offset = offset;
			sprite.atlasSize = Vector2(ratio / width, ratio / height);
			sprite.duration = duration;

			mSprites.push_back(sprite);
		}
	}
	
	void Animation::Binds()
	{
		// texture bind
		mAtlas->BindShader(graphics::eShaderStage::PS, 12);

		// AnimationCB
		renderer::AnimatorCB data = {};

		data.spriteLeftTop = mSprites[mIndex].leftTop;
		data.spriteSize = mSprites[mIndex].size;
		data.spriteOffset = mSprites[mIndex].offset;
		data.atlasSize = mSprites[mIndex].atlasSize;

		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Animator];
		cb->SetData(&data);

		cb->Bind(eShaderStage::VS);
		cb->Bind(eShaderStage::PS);
	}
	
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}
}