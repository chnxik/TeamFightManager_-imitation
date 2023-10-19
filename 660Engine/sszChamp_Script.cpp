#pragma once
#include "sszChamp_Script.h"

#include "sszBattleManager.h"
#include "sszTGM.h"
#include "sszChamp.h"

namespace ssz
{
	Champ_Script::Champ_Script()
		: mRoot(nullptr)
		, fDamageRatio(0.f)
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
		if(TGM::IsGaming())
			mRoot->Run();
	}

	void Champ_Script::LateUpdate()
	{
		// y값에 따라 z값 변경
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 ChampPos = tr->GetPosition();
		ChampPos.z = (ChampPos.y - TGM::GetStadiumSize().bottom) / TGM::GetStadiumScale().y;
		ChampPos.z *= 0.0001f;
		ChampPos.z += 1.2f; // 경기장 z값

		if (0.f < fDamageRatio)
		{
			fDamageRatio -= 3.f * (float)Time::DeltaTime();

			if (fDamageRatio < 0.f)
				fDamageRatio = 0.f;
		}
		
		tr->SetPosition(ChampPos);
	}

	void Champ_Script::Binds()
	{
		// AnimationCB
		renderer::ChampCB data = {};

		data.DamagedTime = fDamageRatio;
		
		ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Champ];
		cb->SetData(&data);

		cb->Bind(eShaderStage::PS);
	}

	void Champ_Script::BindsClear()
	{
		if (0.f < fDamageRatio)
		{
			renderer::ChampCB data = {};

			data.DamagedTime = 0.f;

			ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Champ];
			cb->SetData(&data);

			cb->Bind(eShaderStage::PS);
		}
	}

	void Champ_Script::DamageCBClear()
	{
		// AnimationCB
		if (0.f < fDamageRatio)
		{
			renderer::ChampCB data = {};
		
			data.DamagedTime = 0.f;
		
			ConstantBuffer* cb = renderer::constantBuffer[(UINT)eCBType::Champ];
			cb->SetData(&data);
		
			cb->Bind(eShaderStage::PS);
		}
	}
	
	std::shared_ptr<AI::AIBB> Champ_Script::InstantiateAIBB()
	{
		std::shared_ptr<AI::AIBB> BB = std::make_shared<AI::AIBB>();
		BB->AddData<std::wstring>(CHAMPKEY, &(GetOwner()->GetName()));
		BB->AddData<GameObject>(GetOwner()->GetName(), GetOwner());
		BB->AddData<GameObject>(L"Cursor", TGM::GetCursor());
		BB->CreateData<Vector2>(MOVEPOINT);

		return BB;
	}

	AI::Root_Node* Champ_Script::GetRootNode()
	{
		return mRoot;
	}
	
	void Champ_Script::Attack()
	{
		Champ* Owner = (Champ*)GetOwner();

		if (Owner->GetTarget_Enemy() != nullptr)
		{
			BattleManager::ATTACK(Owner, Owner->GetTarget_Enemy(), Owner->GetChampInfo().ATK);
		}
		
	}

	void Champ_Script::AttackComplete()
	{
		Champ* Owner = (Champ*)GetOwner();
		Owner->GetChampStatus()->accTime_Attack = 0.f;
	}

	void Champ_Script::Heal()
	{
		Champ* Owner = (Champ*)GetOwner();

		if (Owner->GetTarget_Friendly() != nullptr)
		{
			BattleManager::Heal(Owner, Owner->GetTarget_Friendly(), Owner->GetChampInfo().ATK);
		}
	}

	void Champ_Script::HealComplete()
	{
		Champ* Owner = (Champ*)GetOwner();
		Owner->GetChampStatus()->accTime_Attack = 0.f;
	}

	void Champ_Script::ResetAIBB()
	{
		mRoot->Clear();
		std::shared_ptr<AI::AIBB> BB = mRoot->GetAIBB();
		BB->SetRunningNode(nullptr);
		*(BB->FindData<Vector2>(MOVEPOINT)) = Vector2(0,0);
	}
	
	AI::Root_Node* Champ_Script::CreateRootNode(std::shared_ptr<AI::AIBB> pAIBB)
	{
		mRoot = new ssz::AI::Root_Node(pAIBB);
		return mRoot;
	}
}