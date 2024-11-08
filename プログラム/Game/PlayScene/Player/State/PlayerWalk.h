/*
* @file		PlayerWalk.h
* @brief	プレイヤーの歩き状態
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWalk : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerWalk(Player* player);

	//		デストラクタ
	~PlayerWalk();

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

	//		加速処理
	void AccelerationProcess();

private:
	//		加速の速度
	const float ACCELERATION_SPEED = 70.0f;

private:
	//		状態管理クラスのポインタ
	Player* m_player;

	//		初期の高さ
	float m_firstHeight;

	//		速度
	float m_speed;

	//		キーを押しているかどうか
	bool m_keyInputJudgement;

	//		加速するかどうか
	bool m_accelerationJudgement;
};
