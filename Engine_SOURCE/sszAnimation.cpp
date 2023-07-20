#include "sszAnimation.h"
#include "sszTime.h"
#include "sszAnimator.h"

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
	}
	
	void Animation::LateUpdate()
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
	
	void Animation::Render()
	{
	}
	
	void Animation::Create(std::wstring name, std::shared_ptr<graphics::Texture> atlas, Vector2 leftTop, Vector2 size, UINT columnLength, Vector2 offset, float duration)
	{
		SetKey(name);
		mAtlas = atlas;

		float width = (float)atlas->GetWidth();
		float height = (float)atlas->GetHeight();

		for (size_t i = 0; i < columnLength; i++)
		{
			Sprite sprite = {};
			sprite.leftTop.x = leftTop.x + (i * size.x) / width;
			sprite.leftTop.y = leftTop.y / height;
			sprite.size = size;
			sprite.offset = offset;
			sprite.duration = duration;

			mSprites.push_back(sprite);
		}
	}
	
	void Animation::Binds()
	{
		// texture bind
		mAtlas->BindShader(graphics::eShaderStage::PS, 12);

		// AnimationCB
	}
	
	void Animation::Reset()
	{
		mTime = 0.0f;
		mbComplete = false;
		mIndex = 0;
	}
}