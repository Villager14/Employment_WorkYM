/*
* @file		PlayerStart.h
* @brief	プレイヤーのスタート状態
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerStart : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerStart(Player* player);

	//		デストラクタ
	~PlayerStart();

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
	
private:

	//		状態管理クラスのポインタ
	Player* m_player;
};
