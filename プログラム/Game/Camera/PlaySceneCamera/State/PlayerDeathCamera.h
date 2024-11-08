/*
* @file		PlayerDeathCamera.h
* @brief	プレイヤーの死亡カメラ
* @author	Morita
* @date		2024/05/22
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerDeathCamera : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerDeathCamera(PlayerCameraManager* playerCameraManager);
	//		デストラクタ
	~PlayerDeathCamera();
	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	void Finalize() override;

private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;
};
