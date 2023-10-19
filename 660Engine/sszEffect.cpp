#include "sszEffect.h"
#include "CommonHeader.h"

namespace ssz
{
	static int iEffectNumb = 0;

	Effect::Effect()
		: bPlay(false)
		, iefcNumb(iEffectNumb++)
	{
	}

	Effect::~Effect()
	{
	}
	
	void Effect::Initialize()
	{
		SetLayerType(eLayerType::Effect);


		SkillInit();

		
	}

	void Effect::SkillInit()
	{
		// Effect Obj Init
		std::wstring mtkey = L"EffectMt_" + std::to_wstring(iefcNumb);
		LoadMaterial(mtkey, L"AnimationShader", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", mtkey);
		Animator* Anim = AddComponent<Animator>();
		
		// Audio Init
		AudioSource* As = AddComponent<AudioSource>();
		
		// knight
		{
			Resources::Load<AudioClip>(L"knight_skill", L"..\\Resources\\useResource\\Audio\\Buff2.wav");

			// Effect Anim Init
			Resources::Load<Texture>(L"knight_skill_efc", L"..\\Resources\\useResource\\ChampSprite\\knight\\effect\\Knight_Skill_effect.png");
			Anim->Create(L"knight_skill", L"knight_skill_efc", Vector2(0.f, 0.f), Vector2(96.f, 96.f), 8, Vector2(0.f, 0.f), 10.f);
			Anim->CompleteEvent(L"knight_skill") = std::bind(&Effect::Complete, this);
		}

		// healing
		{
			Resources::Load<AudioClip>(L"heal_receive_front", L"..\\Resources\\useResource\\Audio\\healing.wav");

			// Effect Anim Init
			Resources::Load<Texture>(L"healing_efc", L"..\\Resources\\useResource\\ChampSprite\\healing\\heai_efc.png");
			Anim->Create(L"heal_receive_front", L"healing_efc", Vector2(0.f, 0.f), Vector2(38.f, 39.f), 6, Vector2(0.f, 0.f), 10.f);
			Anim->Create(L"heal_receive_back", L"healing_efc", Vector2(0.f, 39.f), Vector2(38.f, 39.f), 6, Vector2(0.f, 0.f), 10.f);
			
			Anim->CompleteEvent(L"heal_receive_front") = std::bind(&Effect::Complete, this);
			Anim->CompleteEvent(L"heal_receive_back") = std::bind(&Effect::Complete, this);
		}
	}
	
	void Effect::Play(Vector3 vPos, Vector3 Scale, const std::wstring& animkey)
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 Pos = vPos;
		Pos.z -= 0.00001f;

		tr->SetPosition(Pos);
		tr->SetScale(Scale);

		GetComponent<Animator>()->PlayAnimation(animkey, false);
		AudioSource* As = GetComponent<AudioSource>();
		As->SetClip(animkey);
		if(As->GetClip())
			As->Play();

		SceneManager::GetActiveScene()->AddGameObject(eLayerType::Effect, this);
		SetActive();

		bPlay = true;
	}
	void Effect::Complete()
	{
		SetPaused();
		bPlay = false;
		SceneManager::GetActiveScene()->Erase(GetLayerType(), this);
	}
}