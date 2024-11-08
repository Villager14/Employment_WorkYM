/*
* @file		PlayerDash.h
* @brief	プレイヤーのダッシュ
* @author	Morita
* @date		2024/04/29
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerDash : public IPlayer
{
public:

	/*
	*	コンストラクタ
	*
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerDash(Player* player);

	//		デストラクタ
	~PlayerDash();

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

	//		加速処理
	void Acceratation();

	void Deceleration();

	//		状態遷移判断
	void ChangeStateJudgement();

private:

	//		ダッシュの最高速度
	const float DASH_MAX_SPEED = 110.0f;

private:

	//		状態管理クラスのポインタ
	Player* m_player;

	//		加速
	float m_acceraration;

	//		減速
	float m_deceleration;

	//		キーを押しているかどうか
	bool m_keyInputJudgement;

	//		移動方向
	DirectX::SimpleMath::Vector3 m_direction;

	//		初期の速さ
	float m_firstSpeed;

	//		初期の高さ
	float m_firstHeight;
};
