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

class PlayerWallWalkCamera : public IPlayerCamera
{
public:

	//		コンストラクタ
	PlayerWallWalkCamera(PlayerCameraManager* playerCameraManager);

	//		デストラクタ
	~PlayerWallWalkCamera();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		終了処理
	void Finalize() override;

	//		角度の返還処理
	/*
	*	角度変換処理
	* 
	*	@param	(radian)	角度
	*	@return 角度
	*/
	void RadianConversion(float* cameraangle, float* velocityRadian);


private:

	//		カメラマネージャーのインスタンスのポインタ
	PlayerCameraManager* m_playerCameraManager;

	//		経過時間
	float m_time;
};
