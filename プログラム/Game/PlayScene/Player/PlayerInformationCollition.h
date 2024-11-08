/*
* @file		PlayerInformationCollition
* @brief	当たり判定用プレイヤーの情報
* @author	Morita
* @date		2024/05/16
*/

#pragma once

#include "pch.h"

class PlayerInformationCollition
{
public:
	//		コンストラクタ
	PlayerInformationCollition()
	:
		m_slidingJudgement(false)
	{};

	//		デストラクタ
	~PlayerInformationCollition() {};


private:

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	//		プレイヤーの高さ
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		スライディングをしているかどうか
	bool m_slidingJudgement;

	//		壁移動時の法線
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;
	
public:

	/*
	*	プレイヤーの座標を受け取る
	* 
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerPosition() { return m_playerPosition; }

	/*
	*	プレイヤーの座標を設定する
	* 
	*	@param	(position)	座標
	*/
	void SetPlayerPosition(const DirectX::SimpleMath::Vector3& position) { m_playerPosition = position; }

	/*
	*	プレイヤーの高さを受け取る
	*
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerHeight() { return m_playerHeight; }

	/*
	*	プレイヤーの高さを設定する
	*
	*	@param	(position)	座標
	*/
	void SetPlayerHeight(const DirectX::SimpleMath::Vector3& position) { m_playerHeight = position; }

	/*
	*	壁移動時の法線を受け取る
	*
	*	@return 法線
	*/
	const DirectX::SimpleMath::Vector3& GetWallWalkNormalize() { return m_wallWalkNormalize; }

	/*
	*	壁移動時の法線を設定する
	*
	*	@param	(normalize)	法線
	*/
	void SetWallWalkNormalize(const DirectX::SimpleMath::Vector3& normalize) { m_wallWalkNormalize = normalize; }

	/*
	*	スライディングをしているか受け取る
	*	
	*	@return true : スライディングしている false : スライディングしていない
	*/
	bool GetSlidingJudgement() { return m_slidingJudgement; }

	/*
	*	スライディングしているかどうか設定する
	* 
	*	@parma	(judgement)	true : スライディングしている false : スライディングしていない
	*/
	void SetSlidingJudgement(bool judgement) { m_slidingJudgement = judgement; }

};


