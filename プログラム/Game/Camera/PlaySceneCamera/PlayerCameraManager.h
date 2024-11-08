/*
* @file		PlayerCameraManager.h
* @brief	プレイヤーのカメラのマネージャー
* @author	Morita
* @date		2024/05/08
*/

#pragma once

#include "IPlayerCamera.h"

#include "State/DebugCamera.h"
#include "State/PlayerCamera.h"
#include "State/PlayerWallWalkCamera.h"
#include "State/PlayerStartCamera.h"
#include "State/PlayerDeathCamera.h"
#include "State/PlayerCameraStop.h"
#include "State/PlayerGoalCamera.h"

#include "Game/PlayScene/Player/PlayerInformation.h"

#include "PlayerCameraInformation.h"

#include "Game/PlayScene/GameManager/GameManager.h"

#include <unordered_map>

class DebugCamera;
class PlayerCamera;
class PlayerWallWalkCamera;
class PlayerStartCamera;
class PlayerDeathCamera;
class PlayerCameraStop;
class PlayerGoalCamera;


class PlayerCameraManager
{
public:
	//		コンストラクタ
	PlayerCameraManager(GameManager* gameManager);

	//		デストラクタ
	~PlayerCameraManager();

	//		初期化処理
	void Initialize(PlayerInformation* playerInformation);

	/*
	*	更新処理
	* 
	*	@param	(playerPosition)	プレイヤーの座標
	*/
	void Update();

	//		終了処理
	void Finalize();

	//		カメラの移動処理
	void CameraMove();

	//		視野角
	void ViewingAngle();

	//		視野角の更新
	void ViewAngleUpdate(PlayerInformation* playerInformation);

public:

	//		カメラのタイプ
	enum CameraType
	{
		Debug,
		Standard,
		WallWalk,
		Start,
		Stop,
		Goal,
		Death,
	};

private:

	//		状態
	IPlayerCamera* m_state;

	//		カメラの情報
	std::unique_ptr<PlayerCameraInformation> m_information;

	//		カメラ用プレイヤーの情報
	PlayerInformation* m_playerInformation;
	
	//		ゲームマネージャー
	GameManager* m_gameManager;

	//		派生クラスの格納
	std::unordered_map<CameraType, std::unique_ptr<IPlayerCamera>> m_stateInformation;

	//		現在のカメラタイプ
	CameraType m_cameraType;

	//		現在の視野角
	float m_nowViewAngle;

	//		開始時の方法
	float m_startDirection;

public:
	/*
	*	カメラの状態の切り替え
	* 
	*	@param	(type)	カメラの種類
	*/
	void ChangeState(CameraType type);


	/*
	*	ゲームマネージャーを受け取る
	* 
	*	@return ゲームマネージャーのインスタンスのポインタ
	*/
	GameManager* GetGameManager() { return m_gameManager; }

	/*
	*	カメラの情報を受け取る
	* 
	*	@return インスタンスのポインタ
	*/
	PlayerCameraInformation* GetInformation() { return m_information.get(); }
	
	/*
	*	プレイヤーの情報を受け取る
	* 
	*	@return プレイヤーの情報
	*/
	PlayerInformation* GetPlayerInformationCamera() { return m_playerInformation; }

	/*
	*	開始時の方法を設定する
	* 
	*	@param	(direction)	角度
	*/
	void SetStartDirection(float direction) { m_startDirection = direction; }

	/*
	*	開始時の方向を受け取る
	* 
	*	@return 角度
	*/
	float GetStartDirection() { return m_startDirection; }
};
