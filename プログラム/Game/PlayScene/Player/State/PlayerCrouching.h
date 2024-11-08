/*
* @file		class PlayerCrouching.h
* @brief	プレイヤーのしゃがみ状態
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "../IPlayer.h"

class Player;

class PlayerCrouching : public IPlayer
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(player) 状態管理クラスのポインタ
	*/
	PlayerCrouching(Player* player);

	//		デストラクタ
	~PlayerCrouching();

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

	//		速度処理
	void SpeedProcessing();
	
private:

private:

	//		状態管理クラスのポインタ
	Player* m_player;

	//		初期しゃがみ高さ
	float m_firstHeight;

	//		キーを押しているかどうか
	bool m_keyInputJudgement;
};
