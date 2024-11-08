/*
* @file		PlayerFall.h
* @brief	プレイヤーの落下状態
* @author	Morita
* @date		2024/07/19
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerFall : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerFall(Player* player);

	//		デストラクタ
	~PlayerFall();

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

	//		状態遷移判断
	void ChangeStateJudgement();
	
	void MoveProcess();

private:

	//		状態管理クラスのポインタ
	Player* m_player;

	float m_firstHeight;

	float m_speed;

	bool m_rayHitJudgement;

	//		キーを押しているかどうか
	bool m_keyInputJudgement;

	//		カメラのマトリックス情報
	DirectX::SimpleMath::Matrix m_cameraMatrix;
};
