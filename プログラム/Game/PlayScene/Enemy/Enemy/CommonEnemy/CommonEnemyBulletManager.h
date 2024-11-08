/*
* @file		CommonEnemyBulletManager.h
* @brief	一般的な敵の弾のマネージャー
* @author	Morita
* @date		2024/05/06
*/

#pragma once

#include "CommonEnemyBullet.h"

class CommonEnemyBulletManager
{
public:

	//		コンストラクタ
	CommonEnemyBulletManager();

	//		デストラクタ
	~CommonEnemyBulletManager();

	/*
	*	エネミーの数
	* 
	*	@param	(enemyCount)	エネミーの数
	*/
	void Initialize(int enemyCount);

	/*
	*	更新処理
	*	
	*	@param	(timeSpeed)	時間の速度
	*/
	void Update(float timeSpeed);

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

private:

	//		弾
	std::vector<std::unique_ptr<CommonEnemyBullet>> m_bullet;

	//		弾の座標
	std::vector<DirectX::SimpleMath::Vector3> m_bulletPosition;

public:

	/*
	*	弾の発射
	*	
	*	@param	(position)	発射座標
	*	@param	(velocity)	発射方向
	*/
	void Firing(const DirectX::SimpleMath::Vector3& position,
		const DirectX::SimpleMath::Vector3& velocity);

	/*
	*	弾の座標を受け取る
	* 
	*	@return 座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetBulletPosition() { return m_bulletPosition; }

};