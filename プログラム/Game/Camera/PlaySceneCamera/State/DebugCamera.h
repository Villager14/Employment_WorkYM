/*
* @file		DebugCamera.h
* @brief	デバックカメラ
* @author	Morita
* @date		2024/04/23
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class DebugCamera : public IPlayerCamera
{
public:
	
	//		コンストラクタ
	DebugCamera(PlayerCameraManager* playerCameraManager);

	//		デストラクタ
	~DebugCamera();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;

};


