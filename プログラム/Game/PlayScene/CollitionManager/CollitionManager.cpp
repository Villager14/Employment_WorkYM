/*
* @file		CollitionManager.cpp
* @brief	当たり判定マネージャー
* @author	Morita
* @date		2024/04/16
*/

#include "pch.h"

#include "CollitionManager.h"

CollitionManager::CollitionManager(GameManager* gameManager)
	:
	m_gameManager(gameManager)
{
	//		メッシュの当たり判定の生成
	m_meshCollition = std::make_unique<MeshCollitionManager>(gameManager);

	//		当たり判定の情報
	m_collitionInformation = std::make_unique<CollitionInformation>();
}

CollitionManager::~CollitionManager()
{
}

void CollitionManager::Initialize()
{
	//		初期化処理の
	//m_meshCollition->Initialize();

	//		弾の当たり判定の生成
	//m_bulletCollition = std::make_unique<BulletCollition>();

}

void CollitionManager::Update(PlayerInformationCollition* playerInformationCollition)
{
	//		当たり判定の初期化
	m_meshCollition->MeshHitPointClear();

	//		法線を送る
	m_meshCollition->SetWallWalkNormalize(playerInformationCollition->GetWallWalkNormalize());

	//		プレイヤーの高さを求める
	float height = playerInformationCollition->GetPlayerHeight().y - playerInformationCollition->GetPlayerPosition().y;

	//		プレイヤーの座標を受け取る
	m_playerPosition = playerInformationCollition->GetPlayerPosition();

	//		以前の当たり判定を削除する
	m_collitionInformation->Clear();

	//		静的な当たり判定
	for (int i = 0; i < m_objectMesh.size(); ++i)
	{
		if (m_objectMesh[i]->GetStaticObjectJudgement())
		{
			CollitionProcess(playerInformationCollition, height, i);

			/*
			//		メッシュの当たり判定
			m_meshCollition->MeshCollition(m_objectMesh[i], m_playerPosition, height, 
								playerInformationCollition->GetSlidingJudgement(), m_gameManager);

			//		床の当たり判定の情報を設定する
			m_collitionInformation->FloorMeshInformation(m_meshCollition->GetMeshHitPoint(),
				m_meshCollition->GetFloorNormalize(), m_playerPosition);

			//		天井に当たっている場合
			if (m_meshCollition->GetHeadHitJudgement())
			{
				//		当たっている
				m_collitionInformation->SetCeilingJudgement(true);
			}

			//		壁の当たり判定情報を設定する
			m_playerPosition = m_collitionInformation->WallMeshInformation(
					m_meshCollition->GetMeshWallHit(),
					m_meshCollition->GetWallHitNormalize(),
					m_meshCollition->GetWallWalkPlayerPosition(),
					m_playerPosition);
			*/
		}
	}

	if (m_collitionInformation->GetFloorMeshHitPoint().size() > 0)
	{
		m_playerPosition = m_collitionInformation->GetFloorMeshHitPoint()[0];

		m_meshCollition->SetPastPlayerPosition(m_playerPosition);
	}
	else
	{
		m_meshCollition->SetPastPlayerPosition(m_playerPosition);
	}

	//		弾の当たり判定
	//m_bulletCollition->Collition(playerInformationCollition->GetPlayerPosition(), playerInformationCollition->GetPlayerHeight(), m_bulletPosition);
}

void CollitionManager::CollitionProcess(
	PlayerInformationCollition* playerInformationCollition, float height,
	int index)
{
	//		メッシュの当たり判定
	m_meshCollition->MeshCollition(m_objectMesh[index], m_playerPosition, height,
		playerInformationCollition->GetSlidingJudgement(), m_gameManager);

	//		床の当たり判定の情報を設定する
	m_collitionInformation->FloorMeshInformation(m_meshCollition->GetMeshHitPoint(),
		m_meshCollition->GetFloorNormalize(), m_playerPosition);

	//		天井に当たっている場合
	if (m_meshCollition->GetHeadHitJudgement())
	{
		//		当たっている
		m_collitionInformation->SetCeilingJudgement(true);
	}

	//		壁の当たり判定情報を設定する
	m_playerPosition = m_collitionInformation->WallMeshInformation(
		m_meshCollition->GetMeshWallHit(),
		m_meshCollition->GetWallHitNormalize(),
		m_meshCollition->GetWallWalkPlayerPosition(),
		m_playerPosition);
}

void CollitionManager::Finalize()
{
	m_meshCollition->Finalize();
	m_collitionInformation->Finalize();
}
