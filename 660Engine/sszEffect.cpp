#include "sszEffect.h"
#include "CommonObjHeader.h"

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

		// Effect Obj Init
		wstring mtkey = L"EffectMt_" + std::to_wstring(iefcNumb);
		LoadMaterial(mtkey, L"AnimationShader", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", mtkey);
		Animator* Anim = AddComponent<Animator>();

		// Effect Anim Init

		Resources::Load<Texture>(L"knight_skill_efc", L"..\\Resources\\useResource\\ChampSprite\\knight\\effect\\Knight_Skill_effect.png");
		Anim->Create(L"knight_skill", L"knight_skill_efc", Vector2(0.f, 0.f), Vector2(96.f, 96.f), 8, Vector2(0.f, 0.f), 10.f);
		Anim->CompleteEvent(L"knight_skill") = std::bind(&Effect::Complete, this);
	}
	
	void Effect::Play(Vector3 vPos, Vector3 Scale, const std::wstring& animkey)
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 Pos = vPos;
		Pos.z -= 0.00001f;

		tr->SetPosition(Pos);
		tr->SetScale(Scale);

		GetComponent<Animator>()->PlayAnimation(animkey, false);

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