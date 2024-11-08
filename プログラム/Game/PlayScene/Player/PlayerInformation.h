/*
* @file		PlayerInformation.cpp
* @brief	プレイヤーの情報
* @author	Morita
* @date		2024/05/19
*/

#pragma once

#include "pch.h"

class PlayerInformation
{
public:
	//		コンストラクタ
	PlayerInformation() 
		:
		m_position{ 0.0f, 0.0f, 0.0f },
		m_planPosition{ 0.0f, 0 ,0.0f },
		m_heightTime(0.0f),
		m_fallTime(0.0f),
		m_gravity(0.0f),
		m_meshHitJudgement(false),
		m_timeSpeed(1.0f),
		m_dashJudgement(true),
		m_dashCoolTime(0.0f),
		m_jumpJudgement(true),
		m_respownJudgement(false),
		m_headWallMove(0.0f),
		m_stopCamera(false),
		m_wireUseJudgement(false),
		m_playerHeadShakingJudgement(false)
	{};

	//		デストラクタ
	~PlayerInformation() {};

	void Initialize()
	{
		m_position = { 0.0f, 0.0f, 0.0f };
		m_planPosition = { 0.0f, 0 ,0.0f };
		m_playerHeight = { 0.0f, 5.0f, 0.0f };
		m_heightTime = 0.0f;
		m_fallTime = 0.0f;
		m_gravity = 0.0f;
		m_meshHitJudgement = false;
		m_timeSpeed = 1.0f;
		m_dashJudgement = true;
		m_dashCoolTime = 0.0f;
		m_jumpJudgement = true;
		m_respownJudgement = false;
		m_headWallMove = 0.0f;
		m_stopCamera = false;
		m_wireUseJudgement = false;
		m_playerHeadShakingJudgement = false;
		m_acceleration = { 0.0f, 0.0f, 0.0f };
	}

	void Finalize()
	{
		m_position = { 0.0f, 0.0f, 0.0f };
		m_planPosition = { 0.0f, 0 ,0.0f };
		m_playerHeight = { 0.0f, STANDING_HEIGHT, 0.0f };
		m_cameraAngle = DirectX::SimpleMath::Vector2::Zero;
		m_world = DirectX::SimpleMath::Matrix::Identity;
		m_direction = DirectX::SimpleMath::Vector3::Zero;
		m_viewVelocity = DirectX::SimpleMath::Vector3::Zero;
		m_wireMovePosition = DirectX::SimpleMath::Vector3::Zero;
		m_respawnPosition = DirectX::SimpleMath::Vector3::Zero;
		m_wallWalkNormalize = DirectX::SimpleMath::Vector3::Zero;
		m_acceleration = DirectX::SimpleMath::Vector3::Zero;
		m_wirePosition.clear();
		m_heightTime = 0.0f;
		m_fallTime = 0.0f;
		m_gravity = 0.0f;
		m_meshHitJudgement = false;
		m_timeSpeed = 1.0f;
		m_dashJudgement = true;
		m_dashCoolTime = 0.0f;
		m_jumpJudgement = true;
		m_respownJudgement = false;
		m_headWallMove = 0.0f;
		m_stopCamera = false;
		m_wireUseJudgement = false;
		m_playerHeadShakingJudgement = false;
	}

private:

	//		立つ速度
	const float STANDING_SPEED = 3.0f;

	//		歩き速度
	const float WALK_SPEED = 30.0f;

	//		最高速度
	const float MAX_SPEED = 70.0f;

	//		しゃがみ速度 
	const float CROUCHING_SPEED = 30.0f;

	//		プレイヤーの高さ
	const float STANDING_HEIGHT = 4.0f;

	//		しゃがみの高さ
	const float CROUCHING_HEIGHT = 2.5f;

	//		スライディングの高さ
	const float SLIDING_HEIGHT = 2.5f;

	//		減速速度
	const float DECELERATION_SPEED = 80.0f;

	//		壁移動時の最高移動量
	//const float HEAD_MOVE_MAX = 3.0f;
	const float HEAD_MOVE_MAX = 1.0f;

	//		頭の移動速度
	const float HEAD_MOVE_SPEED = 30.0f;

	//		重力の加速度
	const float GRAVITATIONAL_ACCELERATION = 9.80665f;

public:

	/*
	*	歩きの速さ
	*
	*	@return 速度
	*/
	float GetWalkSpeed() { return WALK_SPEED; }

	/*
	*	減速の速さ
	*
	*	@return 速度
	*/
	float GetDecelerationSpeed() { return DECELERATION_SPEED; }

	/*
	*	最高速度
	* 
	*	@return 速度
	*/
	float GetMaxSpeed() { return MAX_SPEED; }

	/*
	*	しゃがみの速さ
	*
	*	@return 速度
	*/
	float GetCrouchingSpeed() { return CROUCHING_SPEED; }

	/*
	*	立っているときの高さ
	*
	*	@return 高さ
	*/
	float GetStandingHeight() { return STANDING_HEIGHT; }

	/*
	*	しゃがむときの高さ
	* 
	*	@return 高さ
	*/
	float GetCrouchingHeight() { return CROUCHING_HEIGHT; }

	/*
	*	スライディングの高さ
	* 
	*	@return 高さ
	*/
	float GetSlidngHeight() { return SLIDING_HEIGHT; }

	/*
	*	頭の最高移動量を受け取る
	*
	*	@reutrn 移動量
	*/
	inline constexpr float GetHeadMoveMAX() const noexcept { return HEAD_MOVE_MAX; }

	/*
	*	頭の移動速度を受け取る
	*
	*	@return 移動速度
	*/
	inline constexpr float GetHeadMoveSpeed() const noexcept { return HEAD_MOVE_SPEED; }

	/*
	*	重力加速度を受け取る
	* 
	*	@return 加速度
	*/
	float GetGravitationalAcceleration() { return GRAVITATIONAL_ACCELERATION; }


private:

	//		プレイヤーの座標
	DirectX::SimpleMath::Vector3 m_position;

	//		移動する予定の座標
	DirectX::SimpleMath::Vector3 m_planPosition;

	//		プレイヤーの高さ
	DirectX::SimpleMath::Vector3 m_playerHeight;

	//		カメラの向いている角度
	DirectX::SimpleMath::Vector2 m_cameraAngle;

	//		落下時間
	float m_fallTime;

	//		重力
	float m_gravity;

	//		時間の速度
	float m_timeSpeed;

	//		加速度
	DirectX::SimpleMath::Vector3 m_acceleration;

	//		メッシュに当たっているかどうか
	bool m_meshHitJudgement;

	//		高さ変動時間
	float m_heightTime;

	//		プレイヤーのワールド座標
	DirectX::SimpleMath::Matrix m_world;

	//		移動する方向
	DirectX::SimpleMath::Vector3 m_direction;

	//		ワイヤーの座標
	std::vector<DirectX::SimpleMath::Vector3> m_wirePosition;

	//		視線ベクトル
	DirectX::SimpleMath::Vector3 m_viewVelocity;

	//		移動するワイヤーの座標
	DirectX::SimpleMath::Vector3 m_wireMovePosition;

	//		リスポーン座標
	DirectX::SimpleMath::Vector3 m_respawnPosition;

	//		ダッシュのクールタイム
	float m_dashCoolTime;

	//		ダッシュができるかどうか
	bool m_dashJudgement;

	//		ジャンプできるかどうか
	bool m_jumpJudgement;

	//		リスポーンするかどうか
	bool m_respownJudgement;

	//		頭の動き
	float m_headWallMove;

	//		壁移動時の法線
	DirectX::SimpleMath::Vector3 m_wallWalkNormalize;

	//		カメラを停止させるか透過
	bool m_stopCamera;

	//		ワイヤーを使うことができるか
	bool m_wireUseJudgement;

	//		プレイヤーの頭を揺らすかどうか
	bool m_playerHeadShakingJudgement;

public:

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
	*	頭の動きを受け取る
	*
	*	@return 移動量
	*/
	float GetHeadMove() { return m_headWallMove; }

	/*
	*	頭の動きを設定する
	*
	*	@parma	移動量
	*/
	void SetHeadMove(float headWallMove) { m_headWallMove = headWallMove; }

	/*
	*	ワールド座標を受け取る
	*
	*	@return ワールド座標
	*/
	const DirectX::SimpleMath::Matrix& GetWorld() { return m_world; }

	/*
	*	ワールド座標を設定する
	*
	*	@param	(world)	ワールド座標
	*/
	void SetWorld(const DirectX::SimpleMath::Matrix& world) { m_world = world; }

	/*
	*	座標を受け取る
	*
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPosition() { return m_position; }

	/*
	*	座標を設定する
	*
	*	@param	(position)	座標
	*/
	void SetPosition(const DirectX::SimpleMath::Vector3& position) { m_position = position; }

	/*
	*	移動予定座標を受け取る
	*
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetPlanPosition() { return m_planPosition; }

	/*
	*	移動予定座標を設定する
	*
	*	@param	(position)	座標
	*/
	void SetPlanPosition(const DirectX::SimpleMath::Vector3& position) { m_planPosition = position; }

	/*
	*	カメラの角度を設定する
	*
	*	@param	(angle)	角度
	*/
	void SetCameraAngle(DirectX::SimpleMath::Vector2 angle) { m_cameraAngle = angle; }

	/*
	*	カメラの角度を受け取る
	*
	*	@return 角度
	*/
	const DirectX::SimpleMath::Vector2& GetCameraAngle() { return m_cameraAngle; }

	/*
	*	プレイヤーの高さを設定する
	*
	*	@param	(position)	高さ
	*/
	void SetPlayerHeight(const DirectX::SimpleMath::Vector3& position) { m_playerHeight = position; }

	/*
	*	プレイヤーの高さを受け取る
	*
	*	@return 高さ
	*/
	const DirectX::SimpleMath::Vector3& GetPlayerHeight() { return m_playerHeight; }

	/*
	*	移動する方向を受け取る
	*
	*	@return 方向
	*/
	const DirectX::SimpleMath::Vector3& GetDirection() { return m_direction; }

	/*
	*	移動する方向を設定する
	*
	*	@param	(direction)	方向
	*/
	void SetDirection(const DirectX::SimpleMath::Vector3& direction) { m_direction = direction; }

	/*
	*	落下時間を設定する
	*
	*	@param	(time)	時間
	*/
	void SetFallTime(const float& time) { m_fallTime = time; }

	/*
	*	落下時間を設定する
	*
	*	@param	(time)	時間
	*/
	float GetFallTime() { return m_fallTime; }

	/*
	*	時間の速度を受け取る
	*
	*	@return 時間の速度
	*/
	const float& GetTimeSpeed() { return m_timeSpeed; }

	/*
	*	時間の速度を設定する
	*
	*	@param	(speed)	速度
	*/
	void SetTimeSpeed(const float& speed) { m_timeSpeed = speed; }

	/*
	*	高さ変動時間を設定する
	*
	*	@param	(time)	時間
	*/
	void SetHeightTime(float time) { m_heightTime = time; }

	/*
	*	高さ変動時間を受け取る
	* 
	*	@return 時間
	*/
	float GetHeightTime() { return m_heightTime; }

	/*
	*	加速度を受け取る
	*
	*	@return 加速度
	*/
	const DirectX::SimpleMath::Vector3& GetAcceleration() { return m_acceleration; }

	/*
	*	加速度を設定する
	*
	*	@param	(acceleration)	加速度
	*/
	void SetAcceleration(const DirectX::SimpleMath::Vector3& acceleration) { m_acceleration = acceleration; }

	/*
	*	重力を設定する
	*
	*	@param	(gravity)	重力
	*/
	void SetGravity(float gravity) { m_gravity = gravity; }

	/*
	*	重力を受け取る
	*
	*	@return 重力
	*/
	float GetGravity() { return m_gravity; }

	/*
	*	ワイヤーの座標を受け取る
	*
	*	@return 座標
	*/
	const std::vector<DirectX::SimpleMath::Vector3>& GetWirePosition() { return m_wirePosition; }

	/*
	*	ワイヤーの座標を設定する
	*
	*	@param	(position)	座標
	*/
	void SetWirePosition(const std::vector<DirectX::SimpleMath::Vector3>& position) { m_wirePosition = position; }

	/*
	*	視線ベクトルを設定する
	*
	*	@param	(velocity)
	*/
	void SetViewVelocity(const DirectX::SimpleMath::Vector3& veloicty) { m_viewVelocity = veloicty; }

	/*
	*	視線ベクトルを受け取る
	* 
	*	@return ベクトル
	*/
	const DirectX::SimpleMath::Vector3& GetViewVelocity() { return m_viewVelocity; }

	/*
	*	ワイヤーの移動座標を受け取る
	*
	*	@return 座標
	*/
	const DirectX::SimpleMath::Vector3& GetWireMovePosition() { return m_wireMovePosition; }

	/*
	*	ワイヤーの移動座標を設定する
	* 
	*	@param	(wirePosition)	座標
	*/
	void SetWireMovePosition(const DirectX::SimpleMath::Vector3& wirePosition) { m_wireMovePosition = wirePosition; }

	/*
	*	リスポーン座標を受け取る
	* 
	*	@return 座標
	*/
	DirectX::SimpleMath::Vector3 GetRespawnPosition() { return m_respawnPosition; }

	/*
	*	リスポーン座標を設定する
	* 
	*	@param	(position)	座標
	*/
	void SetRespawnPosition(DirectX::SimpleMath::Vector3 position) { m_respawnPosition = position; }

	/*
	*	ダッシュをするかどうか判断する
	*
	*	@return true : ダッシュをする できる : ダッシュをできない
	*/
	bool GetDashJudgement() { return m_dashJudgement; }

	/*
	*	ダッシュをしているか設定する
	*
	*	@param	(judgemnet)	true : ダッシュできる false : ダッシュをできない
	*/
	void SetDashJudgement(bool judgement) { m_dashJudgement = judgement; }

	/*
	*	ジャンプをするかどうか判断する
	*
	*	@return true : ジャンプできる false : ジャンプできない
	*/
	bool GetJumpJudgement() { return m_jumpJudgement; }

	/*
	*	ジャンプをしているか設定する
	*
	*	@param	(judgemnet)	true : ジャンプできる false : ジャンプできない
	*/
	void SetJumpJudgement(bool judgement) { m_jumpJudgement = judgement; }

	/*
	*	リスポーンするかどうかを設定する
	*
	*	@param	(judgement)	true : リスポーン状態　false : リスポーン状態ではない
	*/
	void SetRespownJudgement(bool judgement) { m_respownJudgement = judgement; }

	/*
	*	リスポーンするかどうか受け取る
	*
	*	@return true : リスポーン状態　false : リスポーン状態ではない
	*/
	bool GetRespownJugement() { return m_respownJudgement; }

	/*
*	ダッシュのクールタイムを受け取る
*
*	@return 時間
*/
	float GetDashCoolTime() { return m_dashCoolTime; }

	/*
	*	ダッシュのクールタイムを設定する
	*
	*	@param	(time)	時間
	*/
	void SetDashCoolTime(float time) { m_dashCoolTime = time; }

	/*
	*	カメラを停止させるかどうか設定する
	* 
	*	@param	(judgement) true : 停止させる false : 停止を終了する
	*/
	void SetCameraStop(bool judgement) { m_stopCamera = judgement; }
	
	/*
	*	カメラを停止させるかどうか受け取る
	* 
	*	@return true : 停止させる false : 停止を終了する
	*/
	bool GetCameraStop() { return m_stopCamera; }

	/*
	*	ワイヤーを使うことができるか設定する
	* 
	*	@param	(judgement)	true : true 使用できる false : 使用できない
	*/
	void SetWireJudgement(bool judgement) { m_wireUseJudgement = judgement; }

	/*
	*	ワイヤーを使うことができるか受け取る
	* 
	*	@return true : true 使用できる false : 使用できない
	*/
	bool GetWireJudgement() { return m_wireUseJudgement; }

	/*
	*	頭を揺らすかどうか設定する
	* 
	*	@param	(judgement) true : 揺らす false : 揺らさない
	*/
	void SetHeadShakingJudgement(bool judgement) { m_playerHeadShakingJudgement = judgement; }

	/*
	*	頭を揺らすかどうか受け取る
	* 
	*	@return true : 揺らす false : 揺らさない
	*/
	bool GetHeadShakingJudgement() { return m_playerHeadShakingJudgement; }
};