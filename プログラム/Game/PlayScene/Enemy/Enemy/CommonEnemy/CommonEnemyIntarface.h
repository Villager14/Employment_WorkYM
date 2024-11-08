/*
* @file		CommonEnemyIntarface.h
* @brief	普通の敵の情報
* @author	Morita
* @date		2024/08/26
*/

#pragma once

#include "pch.h"

class CommonEnemyIntarface
{
public:

	//		コンストラクタ
	CommonEnemyIntarface()
		:
		m_rotation(0.0f),
		m_attackJudgement(false),
		m_timeSpeed(0.0f),
		m_viewLength(20.0f)
	{};

	//		デストラクタ
	~CommonEnemyIntarface() {};

private:

	//		角度
	float m_rotation;

	//		攻撃するかどうか
	bool m_attackJudgement;

	//		時間の速度
	float m_timeSpeed;

	//		攻撃する方向
	DirectX::SimpleMath::Vector3 m_attakDirection;

	//		座標
	DirectX::SimpleMath::Vector3 m_position;

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_playerPosition;

	float m_viewLength;

	//		回転量（開始）
	DirectX::SimpleMath::Quaternion m_startQuotanion;

	//		回転量（終了）
	DirectX::SimpleMath::Quaternion m_endQuotanion;

public:


	/*
	*	座標を受け取る
	*
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	/*
	*	座標を設定する
	*
	*/
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	/*
	*	角度を設定する
	*
	*	@param	(rotation)	角度
	*/
	void SetRotation(float rotation) { m_rotation = rotation; }

	/*
	*	角度を受け取る
	*
	*	@return 角度
	*/
	float GetRotation() { return m_rotation; }

	/*
	*	攻撃するかどうかを受け取る
	*
	*	@return true : 攻撃する false : 攻撃しない
	*/
	bool GetAttackJudgement() { return m_attackJudgement; }

	/*
	*	攻撃するかどうか設定する
	*
	*	@param	(judgement)	true : 攻撃する false : 攻撃しない
	*/
	void SetAttackJudgement(bool judgement) { m_attackJudgement = judgement; }

	/*
	*	攻撃する方向を設定する
	*
	*	@param	(direction)	方向
	*/
	void SetAttackDirection(const DirectX::SimpleMath::Vector3& direction) { m_attakDirection = direction; }

	/*
	*	攻撃する方向を受け取る
	*
	*	@return 方向
	*/
	const DirectX::SimpleMath::Vector3& GetAttackDirection() { return m_attakDirection; }

	/*
	*	時間の速度を受け取る
	*
	*	@return 速度
	*/
	float GetTimeSpeed() { return m_timeSpeed; }

	/*
	*	時間の速度を設定する
	*
	*	@param	(time)	時間
	*/
	void SetTimeSpeed(float time) { m_timeSpeed = time; }

	/*
	*	プレイヤーの座標を受け取る
	*
	*	@return 座標
	*/
	DirectX::SimpleMath::Vector3 GetPlayerPosition() { return m_playerPosition; }

	/*
	*	プレイヤーの座標を設定する
	*
	*	@param	(position)	座標
	*/
	void SetPlayerPosition(DirectX::SimpleMath::Vector3 position) { m_playerPosition = position; }

	/*
	*	視線の長さを受け取る
	* 
	*	@return 長さ
	*/
	float GetViewLength() { return m_viewLength; }





};