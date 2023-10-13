#include "sszCloudObj.h"
#include "CommonHeader.h"

#include "sszApplication.h"

extern ssz::Application application;

namespace ssz
{
	CloudObj::CloudObj()
		: vPlayArea(0.f)
		, bPlay(false)
		, bReady(false)
		, fReadyTime(0.f)
		, fRatio(0.f)
		, fSpeed(0.f)
		, mDayTime(eDayTime::Day)
	{
	}

	CloudObj::~CloudObj()
	{
	}
	
	void CloudObj::Initialize()
	{
		std::wstring Texkey = L"clouds_";
		std::wstring Texpath = L"..\\Resources\\useResource\\Mainlobby\\Bg\\clouds\\clouds_";

		for (int i = 0; i < 8; ++i)
		{
			std::wstring daynumb = std::to_wstring(i * 3 + (UINT)eDayTime::Day);
			std::wstring sunsetnumb = std::to_wstring(i * 3 + (UINT)eDayTime::Sunset);
			std::wstring nightnumb = std::to_wstring(i * 3 + (UINT)eDayTime::Night);
			
			CloudeTexture[(UINT)eDayTime::Day][i] = Resources::Load<Texture>(Texkey + daynumb, Texpath + daynumb + L".png");
			CloudeTexture[(UINT)eDayTime::Sunset][i] = Resources::Load<Texture>(Texkey + sunsetnumb, Texpath + sunsetnumb + L".png");
			CloudeTexture[(UINT)eDayTime::Night][i] = Resources::Load<Texture>(Texkey + nightnumb, Texpath + nightnumb + L".png");
		}

		fReadyTime = (rand() % 10) + 2.f; // 대기시간 설정

		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		vPlayArea = (float)(rect.right - rect.left) / 2.f;
	}
	
	void CloudObj::Update()
	{
		// 재생중
		if (bPlay)
		{
			Transform* tr = GetComponent<Transform>();

			Vector3 Pos = tr->GetPosition();
			Vector3 Scale = tr->GetScale();
			Pos.x -= fSpeed * DT;

			tr->SetPosition(Pos);

			if (Pos.x < -vPlayArea - (Scale.x / 2.f))
			{
				bPlay = false;
				fRatio = 0.f;
				fReadyTime = (rand() % 5) + 2.f;
			}
		}
		else
		{
			fRatio += DT;
			
			if (fReadyTime < fRatio)
			{
				bPlay = true;

				mCurSize = rand() % 8;
				fSpeed = (rand() % 100) + 30.f;

				Transform* tr = GetComponent<Transform>();
				Vector3 Scale = tr->GetScale();
				

				float yPos = rand() % 220 + 100.f;
				float zPos = tr->GetPosition().z;
				
				Vector3	StartPos = { vPlayArea + Scale.x, yPos, zPos };

				tr->SetPosition(StartPos);
				GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(CloudeTexture[(UINT)mDayTime][mCurSize]);
			}
		}

		GameObject::Update();
	}
	
	void CloudObj::SetMt(UINT idx)
	{
		std::wstring mtkey = L"cloudobj_" + std::to_wstring(idx);
		object::LoadMaterial(mtkey, L"SpriteShader", eRenderingMode::Transparent);
		AddComponent<MeshRenderer>()->SetMeshRenderer(L"RectMesh", mtkey);
		AddComponent<Collider2D>();
	}
	
	void CloudObj::SetDayTime(eDayTime daytime)
	{
		mDayTime = daytime;
		GetComponent<MeshRenderer>()->GetMaterial()->SetTexture(CloudeTexture[(UINT)mDayTime][mCurSize]);
	}
}