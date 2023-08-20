#include "sszCamera.h"
#include "sszApplication.h"

#include "sszSceneManager.h"
#include "sszScene.h"

#include "sszTransform.h"
#include "sszMeshRenderer.h"
#include "sszRenderer.h"
#include "sszText.h"

#include "sszGameObject.h"
#include "sszUIObject.h"

extern ssz::Application application;

namespace ssz
{
	bool CompareZSort(GameObject* a, GameObject* b)
	{
		if (a->GetComponent<Transform>()->GetPosition().z
			<= b->GetComponent<Transform>()->GetPosition().z)
			return false;

		return true;
	}

	Matrix Camera::View = Matrix::Identity;
	Matrix Camera::Projection = Matrix::Identity;

	Camera::Camera()
		: Component(eComponentType::Camera)
		, mType(eProjectionType::OrthoGraphic)
		, mAspectRatio(1.0f)
		, mNear(1.0f)
		, mFar(1000.0f)
		, mSize(1.0f)
		, mLayerMask{}
		, mOpaqueGameObjects{}
		, mCutOutGameObjects{}
		, mTransparentGameObjects{}
		, mView(Matrix::Identity)
		, mProjection(Matrix::Identity)
	{
		EnableLayerMasks();
	}

	Camera::~Camera()
	{
	}
	
	void Camera::Initialize()
	{
	}
	
	void Camera::Update()
	{
	}
	
	void Camera::LateUpdate()
	{
		CreateViewMatrix();
		CreateProjectionMatrix(mType);
		RegisterCameraInRenderer();
	}
	
	void Camera::Render()
	{
		View = mView;
		Projection = mProjection;

		AlphaSortGameObjects();
		ZSortTransparencyGameObjects();
		RenderOpaque();

		DisableDepthStencilState();
		RenderCutOut();
		RenderTransparent();
		EnableDepthStencilState();
	}
	
	bool Camera::CreateViewMatrix()
	{
		Transform* tr = GetOwner()->GetComponent<Transform>();
		Vector3 pos = tr->GetPosition();

		// view Translate Matrix
		mView = Matrix::Identity;
		mView *= Matrix::CreateTranslation(-pos);

		// View Rotation Matrix
		Vector3 up = tr->Up();
		Vector3 right = tr->Right();
		Vector3 Foward = tr->Foward();

		Matrix viewRotate;
		viewRotate._11 = right.x;	viewRotate._12 = up.x;	viewRotate._13 = Foward.x;
		viewRotate._21 = right.y;	viewRotate._22 = up.y;	viewRotate._23 = Foward.y;
		viewRotate._31 = right.z;	viewRotate._32 = up.z;	viewRotate._33 = Foward.z;
		mView *= viewRotate;

		return true;
	}
	
	bool Camera::CreateProjectionMatrix(eProjectionType type)
	{
		RECT rect = {};
		GetClientRect(application.GetHwnd(), &rect);
		float width =	(float)(rect.right - rect.left);
		float height =	(float)(rect.bottom - rect.top);
		mAspectRatio = width / height; // 종횡비

		if (type == eProjectionType::OrthoGraphic)
		{
			float OrthoGraphicRatio = mSize; // Size = 1.f;
			width *= OrthoGraphicRatio;
			height *= OrthoGraphicRatio;

			mProjection = Matrix::CreateOrthographicLH(width, height, mNear, mFar);
		}
		else
		{
			mProjection = Matrix::CreatePerspectiveFieldOfViewLH(XM_2PI / 6.0f, mAspectRatio, mNear, mFar);
		}

		return true;
	}
	
	void Camera::RegisterCameraInRenderer()
	{
		renderer::cameras.push_back(this);
	}
	
	void Camera::TurnLayerMask(eLayerType type, bool enable)
	{
		mLayerMask.set((UINT)type, enable);
	}
	
	void Camera::AlphaSortGameObjects()
	{
		mOpaqueGameObjects.clear();
		mCutOutGameObjects.clear();
		mTransparentGameObjects.clear();

		// alpha sorting
		Scene* scene = SceneManager::GetActiveScene();
		for (size_t i = 0; i < (UINT)eLayerType::End; i++)
		{
			if (mLayerMask[i] == true)
			{
				Layer& layer = scene->GetLayer((eLayerType)i);
				
				if (i == (UINT)eLayerType::UI) // UI Layer
				{
					const std::vector<GameObject*> UIObjs
						= layer.GetGameObjects();

					for (int j = (int)UIObjs.size() - 1; 0 <= j; --j)
					{
						DivideAlphaBlendUIObject((UIObject*)UIObjs[j]);
					}
				}
				else
				{
					const std::vector<GameObject*> gameObjs
						= layer.GetGameObjects();
					
					// layer에 있는 게임오브젝트를 들고온다.
					DivideAlphaBlendGameObjects(gameObjs);
				}
			}
		}
	}
	
	void Camera::ZSortTransparencyGameObjects()
	{
		std::sort(mCutOutGameObjects.begin()
			, mCutOutGameObjects.end()
			, CompareZSort);
		std::sort(mTransparentGameObjects.begin()
			, mTransparentGameObjects.end()
			, CompareZSort);
	}
	
	void Camera::DivideAlphaBlendGameObjects(const std::vector<GameObject*> gameObjs)
	{
		for (GameObject* obj : gameObjs)
		{
			// 렌더러 컴포넌트가 없다면?
			MeshRenderer* mr
				= obj->GetComponent<MeshRenderer>();
			if (mr == nullptr)
			{
				// 렌더러 컴포넌트가 없으나 Text 컴포넌트가 있는경우
				Text* tx = obj->GetComponent<Text>();

				if (tx == nullptr) // Text 컴포넌트도 없는경우
					continue;

				mTransparentGameObjects.push_back(obj);
				continue;
			}
			

			std::shared_ptr<Material> mt = mr->GetMaterial();
			eRenderingMode mode = mt->GetRenderingMode();
			switch (mode)
			{
			case ssz::graphics::eRenderingMode::Opaque:
				mOpaqueGameObjects.push_back(obj);
				break;
			case ssz::graphics::eRenderingMode::CutOut:
				mCutOutGameObjects.push_back(obj);
				break;
			case ssz::graphics::eRenderingMode::Transparent:
				mTransparentGameObjects.push_back(obj);
				break;
			default:
				break;
			}
		}
	}

	void Camera::DivideAlphaBlendUIObject(UIObject* UIObjs)
	{
		static std::queue<UIObject*> UIQueue;
		UIQueue.push(UIObjs);

		while (!UIQueue.empty())
		{
			UIObject* pUI = UIQueue.front();
			UIQueue.pop();

			const std::vector<UIObject*> UIChilds = pUI->GetChildUI();
			for (size_t k = 0; k < UIChilds.size(); ++k)
			{
				UIQueue.push(UIChilds[k]);
			}

			// 렌더러 컴포넌트가 없다면?
			MeshRenderer* mr
				= pUI->GetComponent<MeshRenderer>();
			if (mr == nullptr)
			{
				// 렌더러 컴포넌트가 없으나 Text 컴포넌트가 있는경우
				Text* tx = pUI->GetComponent<Text>();

				if (tx == nullptr) // Text 컴포넌트도 없는경우
					continue;

				mTransparentGameObjects.push_back((GameObject*)pUI);
				continue;
			}

			std::shared_ptr<Material> mt = mr->GetMaterial();
			eRenderingMode mode = mt->GetRenderingMode();
			switch (mode)
			{
			case ssz::graphics::eRenderingMode::Opaque:
				mOpaqueGameObjects.push_back((GameObject*)pUI);
				break;
			case ssz::graphics::eRenderingMode::CutOut:
				mCutOutGameObjects.push_back((GameObject*)pUI);
				break;
			case ssz::graphics::eRenderingMode::Transparent:
				mTransparentGameObjects.push_back((GameObject*)pUI);
				break;
			default:
				break;
			}

		}
	}
	
	void Camera::RenderOpaque()
	{
		for (GameObject* gameObj : mOpaqueGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if(gameObj->IsActive())
				gameObj->Render();
		}
	}
	
	void Camera::RenderCutOut()
	{
		for (GameObject* gameObj : mCutOutGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->IsActive())
				gameObj->Render();
		}
	}
	
	void Camera::RenderTransparent()
	{
		for (GameObject* gameObj : mTransparentGameObjects)
		{
			if (gameObj == nullptr)
				continue;
			if (gameObj->IsActive())
				gameObj->Render();
		}
	}
	
	void Camera::EnableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::Less];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
	
	void Camera::DisableDepthStencilState()
	{
		Microsoft::WRL::ComPtr<ID3D11DepthStencilState> dsState
			= renderer::depthStencilStates[(UINT)eDSType::None];
		GetDevice()->BindDepthStencilState(dsState.Get());
	}
}