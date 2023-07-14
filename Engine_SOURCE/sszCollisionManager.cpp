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
		// �簢�� �浹

		Vector3 vLeftPos = left->GetColliderPos();
		Vector3 vLeftScale = left->GetColliderScale();

		Vector3 vRightPos = right->GetColliderPos();
		Vector3 vRightScale = right->GetColliderScale();

		if (fabsf(vLeftPos.x - vRightPos.x) > (vLeftScale.x / 2.f + vRightScale.x / 2.f))
			return false;

		if (fabsf(vLeftPos.y - vRightPos.y) > (vLeftScale.y / 2.f + vRightScale.y / 2.f))
			return false;

		return true;
	}

	bool CollisionManager::CircleIntersect(Collider2D* left, Collider2D* right)
	{
		// �� �浹

		return false;
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