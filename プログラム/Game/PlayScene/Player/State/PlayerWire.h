/*
* @file		PlayerWire.h
* @brief	プレイヤーのワイヤー状態
* @author	Morita
* @date		2024/05/13
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerWire : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerWire(Player* player);

	//		デストラクタ
	~PlayerWire();

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

	//		引き寄せる時の処理
	void AttractProcess();

	//		加速処理
	void AccelerationProcess();

	//		減速処理
	void DecelerationProcess();

	//		落下時の処理
	void FallProcess();

	//		落下状態にするかどうか
	void FallJudgement();

	//		速度の初期化処理
	void SpeedInitlaize();

private:
	
	//		減速
	const float DECELERATION_SPEED = 8.0f;

	//		最大速度
	const float MAX_SPEED = 150.0f;

	//		加速の割合
	const float ACCELERATION_RATE = 0.7f;

	//		加速の割合速度
	const float ACCELERATION_RATE_SPEED = 3.0f;

private:
	//		状態管理クラスのポインタ
	Player* m_player;

	//		経過時間
	float m_time;

	//		初期の高さ
	float m_firstHeight;

	//		距離
	float m_length;

	//		減速するかどうか
	bool m_decelerationJudgement;

	//		移動方向
	DirectX::SimpleMath::Vector3 m_direction;

	DirectX::SimpleMath::Vector3 m_acceleation;

	//		速度を受け取る
	float m_speed;

	//		初期速度
	float m_firstSpeed;

	//		加速時の最高速度
	float m_accelerationSpeed;

	//		落下判断
	bool m_fallJudgement;

	//		何かに当たった場合
	bool m_floorHitJudgement;

	//		壁に当たったか？
	bool m_wallHitJudgement;
};
