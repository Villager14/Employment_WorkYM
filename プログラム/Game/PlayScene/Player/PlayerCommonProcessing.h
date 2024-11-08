/*
* @file		PlayerCommonProcessing.h
* @brief	プレイヤーの共通処理クラス
* @author	Morita
* @date		2024/07/18
*/

#pragma once

class Player;

class PlayerCommonProcessing
{
public:

	PlayerCommonProcessing(Player* player);

	~PlayerCommonProcessing();

	/*
	*	重力処理
	*
	*	@param	(weekJudgement)	弱い重力にするかどうか
	*/
	void Gravity(bool weekJudgement = false);

	//		床メッシュに当たっているか判断する
	bool FloorMeshHitJudgement();

	//		壁メッシュに当たっているか判断する
	bool WallMeshHitJudgement();

	/*
	*	立つ状態にする
	*
	*	@param	(firstHeight)	最初の高さ
	*	@param	(endHeight)		最終的な高さ
	*	@param	(speed)			速度
	*/
	void PlayerHeightTransition(const float& firstHeight, const float& endHeight, const float& speed);

	//		速度上限
	void SpeedUpperLimit();

	/*
	*	移動処理
	*
	*	@param	(keyPressJudgement)	キーを押したかどうか
	*	@return 移動方向
	*/
	DirectX::SimpleMath::Vector3 Direction(bool* keyPressjudgement);

	/*
	*	移動する向き
	*
	*	@param (direction) 移動したい方向
	*	@return 向き
	*/
	DirectX::SimpleMath::Vector3 MoveDirection
	(const DirectX::SimpleMath::Vector3 direction);

	/*
	*	ワイヤーアクションをするかどうか
	*
	*	@returnr するかどうか true : 行う fales : 行わない
	*/
	bool WireActionJudgement();

	//		壁走り状態になるかどうか
	void WallWalkJudgement();

	//		ダッシュのクールタイム
	void DashCoolTime();

private:

	Player* m_player;
};