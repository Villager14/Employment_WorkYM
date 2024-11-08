/*
* @file		PlayerStay.h
* @brief	プレイヤーの待機状態
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerStay : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerStay(Player* player);

	//		デストラクタ
	~PlayerStay();

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

	//		減速処理
	void Deceleration();

	//		状態遷移判断
	void ChangeStateJudgement();
private:
	
	//		減速
	const float DECELERATION_SPEED = 8.0f;

private:
	//		状態管理クラスのポインタ
	Player* m_player;

	//		経過時間
	float m_time;

	//		初期の高さ
	float m_firstHeight;
};
