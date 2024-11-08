/*
* @file		PlayerSlowTime.cpp
* @brief	プレイヤーの低速時間状態
* @author	Morita
* @date		2024/04/29
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerSlowTime : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerSlowTime(Player* player);

	//		デストラクタ
	~PlayerSlowTime();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		移動処理
	void Move() override;

	//		アニメーションの処理
	void Animation() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

	//		移動処理
	void MoveProcessing();

	//		状態遷移判断
	void ChangeStateJudgement();

private:
	//		状態管理クラスのポインタ
	Player* m_player;

	//		移動方向
	DirectX::SimpleMath::Vector3 m_direction;

	//		カメラのマトリックス情報
	DirectX::SimpleMath::Matrix m_cameraMatrix;

	//		時間
	float m_time;

	//		初期の高さ
	float m_firstHeight;

};
