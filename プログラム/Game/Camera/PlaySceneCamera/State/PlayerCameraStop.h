/*
* @file		PlayerCameraStop.h
* @brief	プレイヤー動かないのカメラ
* @author	Morita
* @date		2024/06/10
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerCameraStop : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerCameraStop(PlayerCameraManager* playerCameraManager);
	//		デストラクタ
	~PlayerCameraStop();
	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	void Finalize() override;

private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;
};
