/*
* @file		CommonEnemyBulletManager.h
* @brief	一般的な敵の弾のマネージャー
* @author	Morita
* @date		2024/05/06
*/

#include "pch.h"

#include "CommonEnemyBulletManager.h"


CommonEnemyBulletManager::CommonEnemyBulletManager()
{
}

CommonEnemyBulletManager::~CommonEnemyBulletManager()
{
}

void CommonEnemyBulletManager::Initialize(int enemyCount)
{
	//		エネミーの数×３の玉を生成する
	for (int i = 0; i < 3 * enemyCount; ++i)
	{
		//		弾の追加
		m_bullet.push_back(std::make_unique<CommonEnemyBullet>());

		//		初期化処理
		m_bullet[i]->Initialize();
	}
}

void CommonEnemyBulletManager::Update(float timeSpeed)
{
	//		解放
	m_bulletPosition.clear();

	for (int i = 0, max = static_cast<int>(m_bullet.size()); i < max; ++i)
	{
		//		発射しているかどうか
		if (!m_bullet[i]->GetFiringJudgement()) continue;
		
		//		更新処理
		m_bullet[i]->Update(timeSpeed);

		//		弾の座標を設定する
		m_bulletPosition.push_back(m_bullet[i]->GetPosition());
	}
}

void CommonEnemyBulletManager::Render()
{
	for (int i = 0, max = static_cast<int>(m_bullet.size()); i < max; ++i)
	{
		//		発射しているかどうか
		if (!m_bullet[i]->GetFiringJudgement()) continue;

		//		更新処理
		m_bullet[i]->Render();
	}
}

void CommonEnemyBulletManager::Finalize()
{
}

void CommonEnemyBulletManager::Firing(const DirectX::SimpleMath::Vector3& position,
									  const DirectX::SimpleMath::Vector3& velocity)
{
	for (int i = 0, max = static_cast<int>(m_bullet.size()); i < max; ++i)
	{
		//		発射しているかどうか
		if (m_bullet[i]->GetFiringJudgement()) continue;

		//		発射状態にする
		m_bullet[i]->SetFiringJudgement(true);

		//		弾の情報を設定する
		m_bullet[i]->SetBulletInformation(position, velocity);
	}
}
