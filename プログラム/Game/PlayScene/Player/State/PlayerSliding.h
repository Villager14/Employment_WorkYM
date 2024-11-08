/*
* @file		PlayerSliding.h
* @brief	プレイヤーのスライディング
* @author	Morita
* @date		2024/04/17
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerSliding : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerSliding(Player* player);
	//		デストラクタ

	~PlayerSliding();

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

	//		坂道かどうか判断する
	void SlopeJudgement();

private:

	//		スライディングの加速
	const float SLIDING_ACCELERATION_SPEED = 20.0f;

	//		スライディングの追加初速
	const float INTIAL_VELOCITY = 5.0f;

private:

	//		状態管理クラスのポインタ
	Player* m_player;

	//		初期の高さ
	float m_firstHeight;

	//		減速速度
	float m_decelerationSpeed;

	//		初期速度
	float m_firstSpeed;

	//		キーを押しているかどうか
	bool m_keyInputJudgement;

	//		速度
	float m_speed;

	//		加速時間
	float m_accelerationTime;

	//		坂かどうか
	bool m_slopeJudgement;

	DirectX::SimpleMath::Vector2 m_slidingVelocity;
};
