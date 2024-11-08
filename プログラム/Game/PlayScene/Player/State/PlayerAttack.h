/*
* @file		PlayerAttack.h
* @brief	プレイヤーの攻撃状態
* @author	Morita
* @date		2024/04/30
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerAttack
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerAttack(Player* player);

	//		デストラクタ
	~PlayerAttack();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		移動処理
	void Move();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

	//		減速処理
	void Deceleration();
	
private:
	//		状態管理クラスのポインタ
	Player* m_player;

	float m_time;
};
