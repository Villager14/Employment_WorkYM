/*
* @file		MeshCollitionManaager.cpp
* @brief	メッシュの当たり判定マネージャー
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "MeshCollitionManager.h"

MeshCollitionManager::MeshCollitionManager(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
	//		メッシュ床の当たり判定の生成
	m_meshCollitionFloor = std::make_unique<MeshCollitionFloor>(this);

	//		メッシュの壁の当たり判定
	m_meshCollitionWall = std::make_unique<MeshCollitionWall>(this);

	//		メッシュの頭の当たり判定
	m_meshCollitionHead = std::make_unique<MeshCollitionHead>(this);

	//		メッシュの共通処理の生成
	m_commonProcessing = std::make_unique<MeshCommonProcessing>();

}

MeshCollitionManager::~MeshCollitionManager()
{
}

void MeshCollitionManager::Initialize()
{
}

void MeshCollitionManager::MeshCollition(ObjectMesh* objectMesh,
			const DirectX::SimpleMath::Vector3& playerPosition,
			float height, bool slidingJudgement,
			GameManager* gameManager)
{
	//		スライディング状態かどうか
	if (slidingJudgement)
	{
		playerUnderRayLength = 1.0f;
	}
	else
	{
		playerUnderRayLength = 0.3f;
	}

	//		レイの長さを設定する
	m_meshCollitionFloor->SetRayLength(playerUnderRayLength, PLAYER_ABOVE_RAY_LENGTH);

	//		壁の当たり判定
	m_wallHit = m_meshCollitionWall->WallCollition(objectMesh, playerPosition, height);

	//		オブジェクトタイプが壁の時
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Wall)
	{
		//		壁に当たった法線
		m_wallHitNormalize = m_meshCollitionWall->GetNormalize();
	}

	//		頭の当たり判定
	m_meshCollitionHead->HeadCollition(objectMesh, playerPosition, height);

	//		オブジェクトタイプがゴールの時
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Goal &&
		m_wallHit.size() != 0)
	{
		//		ゴールを設定する
		//gameManager->SetGoalJudgement(true);
		gameManager->TrueFlag(GameManager::GoalJudgement);
	}

	m_wallWalkPlayerPosition = m_meshCollitionWall->WallWalk(objectMesh, playerPosition);

	if (m_wallHit.size() == 0)
	{
		m_playerPosition = playerPosition;
	}
	else
	{
		m_playerPosition = { m_wallHit[0].x, playerPosition.y, m_wallHit[0].y };
	}

	//		床の当たり判定を更新する
	m_meshHitPoint = m_meshCollitionFloor->FloorCollition(objectMesh, m_playerPosition);

	if (m_meshHitPoint.size() != 0)
	{
		//		ゴールに当たっている場合
		if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::Goal)
		{
			//		ゴールを設定する
			gameManager->TrueFlag(GameManager::GoalJudgement);
		}
	}

	//		ダメージオブジェクトかどうか
	if (objectMesh->GetObjectType() == ObjectMesh::ObjectType::DamageObject)
	{
		DamageHitJudgement();
	}
}

void MeshCollitionManager::MeshHitPointClear()
{
	m_meshHitPoint.clear();
	//		壁の当たり判定を
	m_wallHit.clear();
	m_wallWalkPlayerPosition.clear();
	m_wallHitNormalize.clear();
	m_meshHitPoint.clear();
}

void MeshCollitionManager::DamageHitJudgement()
{
	//		ダメージオブジェクトに当たった場合
	if (m_meshHitPoint.size()	!= 0 ||
		m_wallHit.size()		!= 0 ||
		m_meshCollitionHead->GetHitJudgement())
	{
		//		死亡状態にする
		m_gameManager->TrueFlag(GameManager::DamageObjectHit);
	}
}

void MeshCollitionManager::Finalize()
{
	m_meshHitPoint.clear();
	//		壁の当たり判定を
	m_wallHit.clear();
	m_wallWalkPlayerPosition.clear();
	m_wallHitNormalize.clear();
	m_meshHitPoint.clear();

	m_meshCollitionFloor->Finalize();
	m_meshCollitionWall->Finalize();
}
