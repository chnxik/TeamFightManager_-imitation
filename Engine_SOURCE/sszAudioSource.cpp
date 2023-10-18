#include "sszAudioSource.h"
#include "sszAudioClip.h"
#include "sszTransform.h"
#include "sszGameObject.h"
#include "sszResources.h"

namespace ssz
{
	AudioSource::AudioSource()
		: Component(eComponentType::AudioSource)
		, mAudioClip(nullptr)
	{

	}

	AudioSource::~AudioSource()
	{

	}

	void AudioSource::Initialize()
	{
	}

	void AudioSource::Update()
	{
	}

	void AudioSource::LateUpdate()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();
		Vector3 foward = tr->Foward();

		if(mAudioClip != nullptr)
			mAudioClip->Set3DAttributes(pos, foward);
	}

	void AudioSource::Render()
	{
	}

	void AudioSource::Play()
	{
		mAudioClip->Play();
	}
	void AudioSource::Stop()
	{
		if(mAudioClip)
			mAudioClip->Stop();
	}
	void AudioSource::SetLoop(bool loop)
	{
		mAudioClip->SetLoop(loop);
	}
	void AudioSource::SetClip(const std::wstring& key)
	{
		mAudioClip = Resources::Find<AudioClip>(key);
	}
}