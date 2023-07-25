#include "sszCollisionManager.h"

#include "sszSceneManager.h"

#include "sszScene.h"
#include "sszLayer.h"

#include "sszGameObject.h"
#include "sszUIObject.h"

#include "sszCollider2D.h"

namespace ssz
{
	std::bitset<LAYER_MAX> CollisionManager::mMatrix[LAYER_MAX] = {};
	std::map<UINT64, bool> CollisionManager::mCollisionMap = {};

	void CollisionManager::Initialize()
	{
	}

	void CollisionManager::LateUpdate()
	{
		for (UINT iRow = 0; iRow < (UINT)eLayerType::End; ++iRow)
		{
			for (UINT iCol = iRow; iCol < (UINT)eLayerType::End; ++iCol) // �ߺ� �˻縦 ���ϱ� ���� ���� ������ ���ȣ���� ���� 
			{
				if (mMatrix[iRow][iCol])
				{
					if (iRow == (UINT)eLayerType::UI && (UINT)eLayerType::Cursor)
						UILayerCollision((eLayerType)iRow, (eLayerType)iCol); // UI,Cursor �浹�˻�
					else
						LayerCollision((eLayerType)iRow, (eLayerType)iCol); // �浹�˻�
				}
			}
		}
	}

	void CollisionManager::LayerCollision(eLayerType left, eLayerType right)
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& lefts
			= ActiveScene->GetLayer(left).GetGameObjects();
		const std::vector<GameObject*>& rights
			= ActiveScene->GetLayer(right).GetGameObjects();

		for (size_t LeftIdx = 0; LeftIdx < lefts.size(); ++LeftIdx)
		{
			// ���� �������� �ݶ��̴��� ����� ��� ����
			Collider2D* leftCol = lefts[LeftIdx]->GetComponent<Collider2D>();

			if (nullptr == leftCol) // �浹ü�� ���°��
				continue;

			size_t RightIdx = 0;
			if (left == right)	// �浹�˻��ϴ� �� ���̾ ������ ���, ���߰˻縦 ���ϱ� ���� RightIdx�� LeftIdx���� �����Ѵ�.
			{
				RightIdx = LeftIdx;
			}

			for (; RightIdx < rights.size(); ++RightIdx)
			{
				Collider2D* rightCol = rights[RightIdx]->GetComponent<Collider2D>();

				if (nullptr == rightCol) // �浹ü�� ���� ���
					continue;

				if (lefts[LeftIdx] == rights[RightIdx]) // �浹�˻� ����� �ڱ� �ڽ��� ���
					continue;

				bool bDead = lefts[LeftIdx]->IsDead() || rights[RightIdx]->IsDead(); // �˻� ��� ��ä�� �� ��ü�� Dead�����̴�.

				ColliderCollision(leftCol, rightCol, bDead); // �浹�˻� ����
			}
		}
	}

	void CollisionManager::UILayerCollision(eLayerType UI, eLayerType Cursor)
	{
		Scene* ActiveScene = SceneManager::GetActiveScene();

		const std::vector<GameObject*>& vecUI
			= ActiveScene->GetLayer(UI).GetGameObjects();
		const std::vector<GameObject*>& vecCursor
			= ActiveScene->GetLayer(Cursor).GetGameObjects();

		for (int i = (int)vecUI.size() - 1; 0 <= i; --i)
		{
			// UIObject�浹 �˻�

			static std::queue<UIObject*> CollisionUIQueue;
			CollisionUIQueue.push((UIObject*)vecUI[i]);

			while (!CollisionUIQueue.empty())
			{
				UIObject* pUI = CollisionUIQueue.front();
				CollisionUIQueue.pop();

				const std::vector<UIObject*> ChildUI = pUI->GetChildUI();

				for (size_t j = 0; j < ChildUI.size(); ++j)
				{
					CollisionUIQueue.push(ChildUI[j]);
				}

				Collider2D* UICol = pUI->GetComponent<Collider2D>();
				Collider2D* CursorCol = vecCursor[0]->GetComponent<Collider2D>();
				
				if (UICol == nullptr)
					continue;

				bool bDead = pUI->IsDead() || vecCursor[0]->IsDead();

				ColliderCollision(UICol, CursorCol, bDead); // �浹�˻� ����
			}
		}
	}

	void CollisionManager::ColliderCollision(Collider2D* left, Collider2D* right, bool bDead)
	{
		// �� �浹ü�� ID Ȯ��
		ColliderID ID = {};
		ID.left = left->GetColliderID();
		ID.right = right->GetColliderID();

		// �浹 ������ �����´�
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(ID.id);
		if (mCollisionMap.end() == iter) // �浹������ ����
		{
			mCollisionMap.insert(std::make_pair(ID.id, false));
			iter = mCollisionMap.find(ID.id);
		}

		eColliderType LeftColType = left->GetType();
		eColliderType RightColType = right->GetType();
		bool bCollision = false;

		// Type�� �浹�˻�

		if (eColliderType::Rect == LeftColType && eColliderType::Rect == RightColType) // Rect �浹
		{
			bCollision = RectIntersect(left, right);
		}
		else if (eColliderType::Circle == LeftColType && eColliderType::Circle == RightColType) // Circle �浹
		{
			bCollision = CircleIntersect(left, right);
		}
		else // ȥ�� �浹
		{
			if (eColliderType::Rect == LeftColType)
			{
				bCollision = MixIntersect(left, right);
			}
			else
			{
				bCollision = MixIntersect(right, left);
			}
		}

		if (bCollision) // �浹�ߴ�
		{
			if (iter->second) // �浹���� ����
			{
				if (bDead) // �˻����� Dead �̹Ƿ� �浹ü ���.
				{
					left->OnCollisionExit(right);
					right->OnCollisionExit(left);
					mCollisionMap.erase(iter); // �� ��ü�� �浹������ ����
				}
				else // �浹 ��
				{
					left->OnCollisionStay(right);
					right->OnCollisionStay(left);
				}
			}

			else // �浹���� ����
			{
				if (!bDead) // �˻����� Dead�� �ƴ�.
				{
					//���� �浹
					left->OnCollisionEnter(right);
					right->OnCollisionEnter(left);
					iter->second = true; // �浹���� ����
				}
			}
		}

		else // �浹���� �ʾҴ�
		{
			if (iter->second) // �浹���� ����
			{
				left->OnCollisionExit(right);
				right->OnCollisionExit(left);
				iter->second = false; // �浹���� ����
			}

			if (bDead) // �˻� ����� Dead ����
			{
				mCollisionMap.erase(iter); // �� ��ü�� �浹������ ����
			}
		}

	}

	bool CollisionManager::RectIntersect(Collider2D* left, Collider2D* right)
	{
		// OBB
		{
			Vector3 LeftPos = left->GetColliderPos();
			Vector3 LeftScale = left->GetColliderScale();

			Vector3 RightPos = right->GetColliderPos();
			Vector3 RightScale = right->GetColliderScale();

			Vector3 CenterDir = LeftPos - RightPos; // �� ��ü�� �߽ɳ����� �Ÿ�����
			Vector3 Axis; // ���� ������
			float CenterProjDist; // ������ �������� �� �߽��� ������ �Ÿ� ��Į��
			float r1, r2; // �� ����� �� ������ ��������
			
			//  1. left�� right�� ���� ����
			Axis = left->GetAxis(Collider2D::eAxis::Right);
			CenterProjDist = abs(CenterDir.Dot(Axis));
			
			r1 = LeftScale.x / 2.f;
			r2 = right->GetLength4OBB(Axis);

			if (r1 + r2 < CenterProjDist)
				return false;

			// 2. left�� up�� ���� ����
			Axis = left->GetAxis(Collider2D::eAxis::Up);
			CenterProjDist = abs(CenterDir.Dot(Axis));

			r1 = LeftScale.y / 2.f;
			r2 = right->GetLength4OBB(Axis);

			if (r1 + r2 < CenterProjDist)
				return false;

			// 3. right�� right�� ���� ����
			Axis = right->GetAxis(Collider2D::eAxis::Right);
			CenterProjDist = abs(CenterDir.Dot(Axis));

			r1 = RightScale.x / 2.f;
			r2 = left->GetLength4OBB(Axis);

			if (r1 + r2 < CenterProjDist)
				return false;

			// 4. right�� up�� ���� ����
			Axis = right->GetAxis(Collider2D::eAxis::Up);
			CenterProjDist = abs(CenterDir.Dot(Axis));

			r1 = RightScale.y / 2.f;
			r2 = left->GetLength4OBB(Axis);

			if (r1 + r2 < CenterProjDist)
				return false;
		}

		return true;
	}

	bool CollisionManager::CircleIntersect(Collider2D* left, Collider2D* right)
	{
		// �� �浹
		Vector3 vLeftPos = left->GetColliderPos();
		Vector3 vLeftScale = left->GetColliderScale();
		float LeftRadius = (vLeftScale.x + vLeftScale.y) / 4.f;

		Vector3 vRightPos = right->GetColliderPos();
		Vector3 vRightScale = right->GetColliderScale();
		float RightRadius = (vRightScale.x + vRightScale.y) / 4.f;

		float Distance = sqrt((vRightPos.x - vLeftPos.x) * (vRightPos.x - vLeftPos.x) + (vRightPos.y - vLeftPos.y) * (vRightPos.y - vLeftPos.y));

		if ((LeftRadius + RightRadius) < Distance)
			return false;

		return true;
	}

	bool CollisionManager::MixIntersect(Collider2D* Rect, Collider2D* Circle)
	{
		// �簢 �� ȥ�� �浹 : OBB ����
		{
			Vector3 RectPos = Rect->GetColliderPos();
			Vector3 RectScale = Rect->GetColliderScale();

			Vector3 CirclePos = Circle->GetColliderPos();
			Vector3 CircleScale = Circle->GetColliderScale();

			Vector3 CenterDir = RectPos - CirclePos; // �� ��ü�� �߽ɳ����� �Ÿ�����
			Vector3 Axis; // ���� ������
			float CenterProjDist; // ������ �������� �� �߽��� ������ �Ÿ� ��Į��
			float r1, r2; // �� ����� �� ������ ��������
			
			
			//  1. Rect�� right�� ����
			Axis = Rect->GetAxis(Collider2D::eAxis::Right);
			CenterProjDist = abs(CenterDir.Dot(Axis));

			r1 = RectScale.x / 2.f;
			r2 = CircleScale.x / 2.f;

			if (r1 + r2 < CenterProjDist)
				return false;

			// 2. Rect�� up�� ����
			Axis = Rect->GetAxis(Collider2D::eAxis::Up);
			CenterProjDist = abs(CenterDir.Dot(Axis));

			r1 = RectScale.y / 2.f;
			r2 = CircleScale.y / 2.f;

			if (r1 + r2 < CenterProjDist)
				return false;

			
			// 3. Circle���� right�� ����
			Axis = Circle->GetAxis(Collider2D::eAxis::Right);
			CenterProjDist = abs(CenterDir.Dot(Axis));

			r1 = CircleScale.x / 2.f;
			r2 = Rect->GetLength4OBB(Axis);

			if (r1 + r2 < CenterProjDist)
				return false;

			// 4. Circle���� up�� ����
			Axis = Circle->GetAxis(Collider2D::eAxis::Up);
			CenterProjDist = abs(CenterDir.Dot(Axis));

			r1 = CircleScale.y / 2.f;
			r2 = Rect->GetLength4OBB(Axis);

			if (r1 + r2 < CenterProjDist)
				return false;
		}

		return true;
	}

	const bool CollisionManager::IsCollision(Collider2D* left, Collider2D* right)
	{
		ColliderID ID = {};
		ID.left = left->GetColliderID();
		ID.right = right->GetColliderID();

		// �浹 ������ �����´�
		std::map<UINT64, bool>::iterator iter = mCollisionMap.find(ID.id);
		if (mCollisionMap.end() == iter) // �浹������ ����
			return false;

		return iter->second;
	}

	void CollisionManager::SetLayer(eLayerType left, eLayerType right, bool enable)
	{
		UINT iRow = (UINT)left;
		UINT iCol = (UINT)right;

		if (iRow > iCol)
		{
			UINT iTemp = iRow;
			iCol = iRow;
			iRow = iTemp;
		}

		mMatrix[iRow][iCol] = enable;
	}

	void CollisionManager::Clear()
	{
		mMatrix->reset();
		mCollisionMap.clear();
	}
}