#include "sszNumb.h"
#include "CommonObjHeader.h"

// atlas 350 * 96
// frame 35 * 48

// 0 ~ 9 : 31
// 1 : 18
// 4 : 35

#define DMGNUMB_0	L"dmg_0"
#define DMGNUMB_1	L"dmg_1"
#define DMGNUMB_2	L"dmg_2"
#define DMGNUMB_3	L"dmg_3"
#define DMGNUMB_4	L"dmg_4"
#define DMGNUMB_5	L"dmg_5"
#define DMGNUMB_6	L"dmg_6"
#define DMGNUMB_7	L"dmg_7"
#define DMGNUMB_8	L"dmg_8"
#define DMGNUMB_9	L"dmg_9"
#define HEALNUMB_0	L"heal_0"
#define HEALNUMB_1	L"heal_1"
#define HEALNUMB_2	L"heal_2"
#define HEALNUMB_3	L"heal_3"
#define HEALNUMB_4	L"heal_4"
#define HEALNUMB_5	L"heal_5"
#define HEALNUMB_6	L"heal_6"
#define HEALNUMB_7	L"heal_7"
#define HEALNUMB_8	L"heal_8"
#define HEALNUMB_9	L"heal_9"


namespace ssz
{
	Numb::Numb()
		: mMr(nullptr)
		, test(0)
		, testratio(0.f)
	{
	}

	Numb::~Numb()
	{
	}
	
	void Numb::Initialize()
	{
		Transform* tr = GetComponent<Transform>();
		tr->SetScale(Vector3(0.f, 25.f, 0.f));

		NumbInit();
		mMr = AddComponent<MeshRenderer>();
		mMr->SetMeshRenderer(L"RectMesh", DMGNUMB_0);
	}

	void Numb::Update()
	{
		testratio += DT;
		InsertNumber(eDmgTextType::HEAL,((int)testratio) % 10);

		GameObject::Update();
	}

	void Numb::InsertNumber(eDmgTextType type, UINT numb)
	{
		Transform* tr = GetComponent<Transform>();
		Vector3 vScale = tr->GetScale();
		vScale.x = vScale.y * (31.f/48.f);
		
		wstring mtkey;
		if (type == eDmgTextType::DAMAGE)
			mtkey = L"dmg_";

		else if (type == eDmgTextType::HEAL)
			mtkey = L"heal_";

		mtkey += std::to_wstring(numb);

		mMr->SetMaterial(mtkey);

		if(numb == 1)
			vScale.x = vScale.y * (18.f / 48.f);
		else if(numb == 4)
			vScale.x = vScale.y * (35.f / 48.f);

		tr->SetScale(vScale);
	}
	
	void Numb::NumbInit()
	{
		Resources::Load<Texture>(L"dmg_0_tex", L"..\\Resources\\useResource\\numb\\dmg_0.png");
		Resources::Load<Texture>(L"dmg_1_tex", L"..\\Resources\\useResource\\numb\\dmg_1.png");
		Resources::Load<Texture>(L"dmg_2_tex", L"..\\Resources\\useResource\\numb\\dmg_2.png");
		Resources::Load<Texture>(L"dmg_3_tex", L"..\\Resources\\useResource\\numb\\dmg_3.png");
		Resources::Load<Texture>(L"dmg_4_tex", L"..\\Resources\\useResource\\numb\\dmg_4.png");
		Resources::Load<Texture>(L"dmg_5_tex", L"..\\Resources\\useResource\\numb\\dmg_5.png");
		Resources::Load<Texture>(L"dmg_6_tex", L"..\\Resources\\useResource\\numb\\dmg_6.png");
		Resources::Load<Texture>(L"dmg_7_tex", L"..\\Resources\\useResource\\numb\\dmg_7.png");
		Resources::Load<Texture>(L"dmg_8_tex", L"..\\Resources\\useResource\\numb\\dmg_8.png");
		Resources::Load<Texture>(L"dmg_9_tex", L"..\\Resources\\useResource\\numb\\dmg_9.png");
		Resources::Load<Texture>(L"heal_0_tex", L"..\\Resources\\useResource\\numb\\heal_0.png");
		Resources::Load<Texture>(L"heal_1_tex", L"..\\Resources\\useResource\\numb\\heal_1.png");
		Resources::Load<Texture>(L"heal_2_tex", L"..\\Resources\\useResource\\numb\\heal_2.png");
		Resources::Load<Texture>(L"heal_3_tex", L"..\\Resources\\useResource\\numb\\heal_3.png");
		Resources::Load<Texture>(L"heal_4_tex", L"..\\Resources\\useResource\\numb\\heal_4.png");
		Resources::Load<Texture>(L"heal_5_tex", L"..\\Resources\\useResource\\numb\\heal_5.png");
		Resources::Load<Texture>(L"heal_6_tex", L"..\\Resources\\useResource\\numb\\heal_6.png");
		Resources::Load<Texture>(L"heal_7_tex", L"..\\Resources\\useResource\\numb\\heal_7.png");
		Resources::Load<Texture>(L"heal_8_tex", L"..\\Resources\\useResource\\numb\\heal_8.png");
		Resources::Load<Texture>(L"heal_9_tex", L"..\\Resources\\useResource\\numb\\heal_9.png");

		LoadMaterial(DMGNUMB_0, L"SpriteShader", L"dmg_0_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_1, L"SpriteShader", L"dmg_1_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_2, L"SpriteShader", L"dmg_2_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_3, L"SpriteShader", L"dmg_3_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_4, L"SpriteShader", L"dmg_4_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_5, L"SpriteShader", L"dmg_5_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_6, L"SpriteShader", L"dmg_6_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_7, L"SpriteShader", L"dmg_7_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_8, L"SpriteShader", L"dmg_8_tex", eRenderingMode::Transparent);
		LoadMaterial(DMGNUMB_9, L"SpriteShader", L"dmg_9_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_0, L"SpriteShader", L"heal_0_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_1, L"SpriteShader", L"heal_1_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_2, L"SpriteShader", L"heal_2_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_3, L"SpriteShader", L"heal_3_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_4, L"SpriteShader", L"heal_4_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_5, L"SpriteShader", L"heal_5_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_6, L"SpriteShader", L"heal_6_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_7, L"SpriteShader", L"heal_7_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_8, L"SpriteShader", L"heal_8_tex", eRenderingMode::Transparent);
		LoadMaterial(HEALNUMB_9, L"SpriteShader", L"heal_9_tex",  eRenderingMode::Transparent);
	}
}