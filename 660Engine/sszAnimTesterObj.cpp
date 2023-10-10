#include "sszAnimTesterObj.h"
#include "CommonObjHeader.h"

namespace ssz
{
	AnimTesterObj::AnimTesterObj()
	{
	}

	AnimTesterObj::~AnimTesterObj()
	{
	}
	
	void AnimTesterObj::Initialize()
	{
		// Load Atlas
		std::wstring ChampName = L"priest";				// 클래스이름
		std::wstring AtlasKey = ChampName + L"_sprite";
		std::wstring AtlasPath =
			L"..\\Resources\\useResource\\ChampSprite\\" + ChampName + L"\\" + AtlasKey + L"\\" + ChampName + L".png";
		
		std::shared_ptr<Texture> atlas = Resources::Load<Texture>(AtlasKey, AtlasPath);

		// Set Mesh Renderer
		std::wstring MtKey = AtlasKey + L"Mt";
		LoadMaterial(MtKey, L"AnimationShader", AtlasKey, eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", MtKey);

		std::wstring IdleAnikey = ChampName + L"_idle";
		std::wstring MoveAnikey = ChampName + L"_move";
		std::wstring AttackAnikey = ChampName + L"_attack";
		std::wstring DeadAnikey = ChampName + L"_dead";
		std::wstring SkillAnikey = ChampName + L"_skill";
		std::wstring UltAnikey = ChampName + L"_ultimate";


		// Animation Set

		Animator* anim = AddComponent<Animator>();
		Transform* tr = GetComponent<Transform>();

		tr->SetScale(Vector3(256.f, 256.f, 0.f));
		Vector2 FrmSize(128.f, 128.f);		// frm 사이즈

		anim->Create(IdleAnikey, AtlasKey, Vector2(0.f, 0.f), FrmSize, 
			4, Vector2(0.f, 0.f), 10.f);
		anim->Create(MoveAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 1), FrmSize, 
			8, Vector2(0.f, 0.f), 10.f);
		anim->Create(AttackAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 2), FrmSize, 
			10, Vector2(0.f, 0.f), 10.f);
		anim->Create(DeadAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 3), FrmSize, 
			10, Vector2(0.f, 0.f), 10.f);
		anim->Create(SkillAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 4), FrmSize, 
			9, Vector2(0.f, 0.f), 10.f);
		anim->Create(UltAnikey, AtlasKey, Vector2(0.f, FrmSize.y * 5), FrmSize, 
			10, Vector2(0.f, 0.f), 10.f);

		SetAnimKey(eActiveType::IDLE, IdleAnikey);
		SetAnimKey(eActiveType::MOVE, MoveAnikey);
		SetAnimKey(eActiveType::ATTACK, AttackAnikey);
		SetAnimKey(eActiveType::DEAD, DeadAnikey);
		SetAnimKey(eActiveType::SKILL, SkillAnikey);
		SetAnimKey(eActiveType::ULTIMATE, UltAnikey);

		GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::IDLE], true);
	}
	
	void AnimTesterObj::Update()
	{
		GameObject::Update();

		if (Input::GetKeyDown(eKeyCode::F1))
			GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::IDLE], true);
		else if (Input::GetKeyDown(eKeyCode::F2))
			GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::MOVE], true);
		else if (Input::GetKeyDown(eKeyCode::F3))
			GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::ATTACK], true);
		else if (Input::GetKeyDown(eKeyCode::F4))
			GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::DEAD], true);
		else if (Input::GetKeyDown(eKeyCode::F5))
			GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::SKILL], true);
		else if (Input::GetKeyDown(eKeyCode::F6))
			GetComponent<Animator>()->PlayAnimation(vecAnimKey[(UINT)eActiveType::ULTIMATE], true);
	}
	
}