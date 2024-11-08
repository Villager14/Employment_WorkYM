/*
* @file		EnemyManager.h
* @brief	エネミーマネージャー
* @author	Morita
* @date		2024/04/29
*/

#pragma once

#include "Enemy/CommonEnemy/CommonEnemy.h"

#include "Enemy/CommonEnemy/CommonEnemyBulletManager.h"

#include "Enemy/LoadingEnemyInformation.h"

class EnemyManager
{
public:

	//		コンストラクタ
	EnemyManager();

	//		デストラクタ
	~EnemyManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(timeSPeed)			時間の速度
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update(const float& timeSpeed,
		const DirectX::SimpleMath::Vector3& playerPosition);

	//		描画処理
	void Render();
private:

	//		一般エネミー
	std::vector<std::unique_ptr<CommonEnemy>> m_commonEnemy;

	//		一般エネミーの弾のマネージャー
	std::unique_ptr<CommonEnemyBulletManager> m_commonEnemyBulletManager;

	//		エネミーの情報の読み込み
	std::unique_ptr<LoadingEnemyInformation> m_enemyInformation;

public:

	/*
	*	弾の座標を受け取る
	* 
	*	@return 座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetBulletPosition()
				{ return m_commonEnemyBulletManager->GetBulletPosition(); }
};