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