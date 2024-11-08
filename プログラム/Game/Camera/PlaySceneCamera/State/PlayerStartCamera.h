/*
* @file		PlayerStartCamera.h
* @brief	プレイヤースタートカメラ
* @author	Morita
* @date		2024/05/21
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerStartCamera : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerStartCamera(PlayerCameraManager* playerCameraManager);
	//		デストラクタ
	~PlayerStartCamera();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	void Finalize() override;

private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;

	//		時間
	float m_time;

	//		初期描画
	bool m_firstViewJudgement;
};
