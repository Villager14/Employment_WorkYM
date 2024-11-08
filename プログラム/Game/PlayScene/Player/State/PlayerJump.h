/*
* @file		PlayerWalk.h
* @brief	プレイヤーの歩き状態
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerJump : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerJump(Player* player);

	//		デストラクタ
	~PlayerJump();

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

	//		ジャンプの処理
	void Jump();

	//		状態遷移をするかどうか
	void ChangeStateJudgement();

private:

	//		ジャンプの速さ
	const float JUMP_SPEED = 2.0f;

	//		ジャンプの最高速度
	const float JUMP_MAX_SPEED = 20.0f;

	//		ジャンプの最低速度
	const float JUMP_MIN_SPEED = 2.0f;

private:

	//		状態管理クラスのポインタ
	Player* m_player;

	//		経過時間
	float m_elapsedTime;

	//		キーを押しているかどうか
	bool m_keyInputJudgement;

	//		初期の高さ
	float m_firstHeight;

	//		カメラのマトリックス情報
	DirectX::SimpleMath::Matrix m_cameraMatrix;

	//		停止した状態からジャンプしたかどうか
	bool m_stopJump;

	//		レイの処理の判断
	bool m_rayprocessJudgement;

	//		レイに当たったかどうか判断する
	bool m_rayHitJudgement;

	//		現在の速度
	float m_nowSpeed;
};
