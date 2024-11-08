/*
* @file		PlayerCamera.h
* @brief	プレイヤーのカメラ
* @author	Morita
* @date		2024/03/30
*/

#pragma once

#include "../IPlayerCamera.h"

#include "../PlayerCameraManager.h"

class PlayerCameraManager;

class PlayerCamera : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerCamera(PlayerCameraManager* playerCameraManager);
	//		デストラクタ
	~PlayerCamera();
	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	void Finalize() override;

	//		視点の揺れ
	void ShakingView();

	//		横揺れ
	void HorizontalShaking();

	//		縦揺れ
	void VerticalShaking();

private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;

	//		始点の座標
	DirectX::SimpleMath::Vector3 m_position;

	//		揺れ時間
	float m_shakingTime;

	//		頭を振る割合
	float m_shakingRatio;

	//		頭を動かす速度
	float m_shakingSpeed;
};
