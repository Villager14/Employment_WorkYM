/*
* @file		RespawnManager.h
* @brief	リスポーンマネージャーの処理
* @author	Morita
* @date		2024/10/03
*/

#pragma once

#include "../GameManager/GameManager.h"

#include "RespawnPointRead.h"

class RespawnManager
{
public:
	//		コンストラクタ
	RespawnManager(GameManager* gameManager);

	//		デストラクタ
	~RespawnManager();

	//		初期化処理
	void Initialize();

	/*
	*	更新処理
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update(DirectX::SimpleMath::Vector3 playerPosition);

	/*
	*	当たり判定
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*	@param	(index)				要素数
	*/
	void CollitionProcess(DirectX::SimpleMath::Vector3 playerPosition,
						  int index);

	//		デバック描画
	void DebugRender();

	//		終了処理
	void Finalize();

private:

	//		リスポーンの要素数
	int m_respownIndex;

	//		ゲームマネージャーのインスタンスのポインタ
	GameManager* m_gameManager;

	//		リスポーン座標
	DirectX::SimpleMath::Vector3 m_respawnPosition;

	//		リスポーン座標読み込み
	std::unique_ptr<RespawnPointRead> m_respawnPointRead;

	//		リスポーンの範囲モデル
	std::unique_ptr<DirectX::Model> m_respownRengeModel;

	//		デバック用のワールド座標
	DirectX::SimpleMath::Matrix m_respownRengeWorld;

	//		方向
	float m_direction;

public:

	/*
	*	リスポーン座標を受け取る
	* 
	*	@return 座標
	*/
	DirectX::SimpleMath::Vector3 GetRespownPosition() { return m_respawnPosition; }
	
	/*
	*	リスポーン方向を受け取る
	* 
	*	@return 角度
	*/
	float GetRespownDirection() { return m_direction; }
};
