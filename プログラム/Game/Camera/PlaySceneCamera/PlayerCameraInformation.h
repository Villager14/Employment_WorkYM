/*
* @file		PlayerCameraInformation.cpp
* @brief	プレイヤーのカメラの情報
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "pch.h"

class PlayerCameraInformation
{
public:
	//		コンストラクタ
	PlayerCameraInformation()
		:
		m_angleMin(0.0f),
		m_viewAngle(70.0f),
		m_mouseSpeed(5.0f)
	{};

	//		デストラクタ
	~PlayerCameraInformation() {};

	void Initialize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
	}

	void Finalize()
	{
		m_angleMin = 0.0f;
		m_viewAngle = 70.0f;
		m_mouseSpeed = 5.0f;
		m_angle = { 0.0f, 0.0f };
		m_viewVelocity = DirectX::SimpleMath::Vector3::Zero;
		m_up = DirectX::SimpleMath::Vector3::Zero;
		m_target = DirectX::SimpleMath::Vector3::Zero;
		m_eye = DirectX::SimpleMath::Vector3::Zero;
		m_cameraMove = DirectX::SimpleMath::Vector2::Zero;
	}

public:

	//		最大角度Y
	const float ANGLE_Y_MAX = 50.0f;

	//		最小角度Y
	const float ANGLE_Y_MIN = -50.0f;

private:

	//		視野角
	float m_viewAngle;

	//		マウスの速度
	float m_mouseSpeed;

	//		最小値
	float m_angleMin;

	//		カメラの角度
	DirectX::SimpleMath::Vector2 m_angle;

	//		視線ベクトル
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	DirectX::SimpleMath::Vector3 m_up;

	DirectX::SimpleMath::Vector3 m_target;

	DirectX::SimpleMath::Vector3 m_eye;

	//		カメラの移動量
	DirectX::SimpleMath::Vector2 m_cameraMove;

public:

	/*
	*	視野角を設定する
	* 
	*	@param	(angle)	角度
	*/
	void SetViewAngle(float angle) { m_viewAngle = angle; }

	/*
	*	視野角を受け取る
	* 
	*	@return	角度
	*/
	float GetViewAngle() { return m_viewAngle; }

	/*
	*	カメラの角度を受けとる
	*
	*	@return 角度
	*/
	const DirectX::SimpleMath::Vector2 GetAngle() { return m_angle; }

	/*
	*	カメラの角度を設定する
	*
	*	@param	(angle)	角度
	*/
	void SetAngle(DirectX::SimpleMath::Vector2 angle) { m_angle = angle; }

	/*
	*	視線ベクトルを設定する
	*
	*	@param	(velocity)	ベクトル
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& velicity) { m_viewVelocity = velicity; }

	/*
	*	視線ベクトルを受け取る
	*
	*	@return ベクトル
	*/
	const DirectX::SimpleMath::Vector3& GetViewVelocity() { return m_viewVelocity; }

	/*
	*	Eyeベクトルを設定する
	*
	*	@param	(eye)	視線ベクトル
	*/
	void SetEye(DirectX::SimpleMath::Vector3 eye) { m_eye = eye; }

	/*
	*	Eyeベクトルを受け取る
	*
	*	@return 視線ベクトル
	*/
	DirectX::SimpleMath::Vector3 GetEye() { return m_eye; }

	/*
	*	ターゲットを設定する
	*
	*	@param	(target)	ターゲットベクトル
	*/
	void SetTarget(DirectX::SimpleMath::Vector3 target) { m_target = target; }

	/*
	*	ターゲットを受け取る
	*
	*	@return ターゲット
	*/
	DirectX::SimpleMath::Vector3 GetTarget() { return m_target; }

	/*
	*	アップベクトルを設定する
	*
	*	@param	(up)	アップベクトル
	*/
	void SetUp(DirectX::SimpleMath::Vector3 up) { m_up = up; }

	/*
	*	アップベクトルを受け取る
	*
	*	@return アップベクトル
	*/
	DirectX::SimpleMath::Vector3 GetUP() { return m_up; }

	/*
	*	カメラの移動量を設定する
	*
	*	@param	(move)	移動量
	*/
	void SetCameraMove(DirectX::SimpleMath::Vector2 move) { m_cameraMove = move; }

	/*
	*	カメラの移動量を受け取る
	*
	*	@return 移動量
	*/
	DirectX::SimpleMath::Vector2 GetCameraMove() { return m_cameraMove; }

	/*
	*	カメラ角度の最小値を受け取る
	*
	*	@return 最小値
	*/
	float GetCameraAngleMin() { return m_angleMin; }

	/*
	*	カメラ角度の最小値を設定する
	* 
	*	@param	(angle)	角度
	*/
	void SetCameraAngleMin(float angle) { m_angleMin = angle; }

	/*
	*	マウスの速度を受け取る
	* 
	*	@return	速度
	*/
	float GetCameraSpeed() { return m_mouseSpeed; }

	/*
	*	マウスの速度を設定する
	* 
	*	@param	(speed)
	*/
	void SetCameraSpeed(float speed) { m_mouseSpeed = speed; }

};
