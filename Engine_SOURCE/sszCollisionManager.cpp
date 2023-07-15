#include "sszCollisionManager.h"

#include "sszSceneManager.h"

#include "sszScene.h"
#include "sszLayer.h"

#include "sszGameObject.h"

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
		// �簢 �� ȥ�� �浹

		return false;
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