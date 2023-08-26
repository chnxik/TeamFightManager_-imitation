#include "sszChamp_Script.h"
#include "sszTGM.h"

namespace ssz
{
	Champ_Script::Champ_Script()
		: mRoot(nullptr)
	{
	}

	Champ_Script::~Champ_Script()
	{
		delete mRoot;
	}

	void Champ_Script::Initialize()
	{
	}

	void Champ_Script::Update()
	{
	}

	void Champ_Script::LateUpdate()
	{
		// y값에 따라 z값 변경
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 ChampPos = tr->GetPosition();
		ChampPos.z = (ChampPos.y - TGM::GetStadiumSize().bottom) / TGM::GetStadiumScale().y;
		ChampPos.z *= 0.0001f;
		ChampPos.z += 1.2f; // 경기장 z값
		
		tr->SetPosition(ChampPos);
	}
	
	std::shared_ptr<AIBB> Champ_Script::InstantiateAIBB()
	{
		std::shared_ptr<AIBB> BB = std::make_shared<AIBB>();
		BB->AddData<std::wstring>(CHAMPKEY, &(GetOwner()->GetName()));
		BB->AddData<GameObject>(GetOwner()->GetName(), GetOwner());
		BB->AddData<GameObject>(L"Cursor", TGM::GetCursor());
		BB->CreateData<Vector2>(MOVEPOINT);

		return BB;
	}
}