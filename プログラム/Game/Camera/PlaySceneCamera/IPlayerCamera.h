/*
* @file		IPlayerCamera.h
* @brief	プレイヤーのカメラのインターフェイス
* @author	Morita
* @date		2024/05/08
*/

#pragma once

class IPlayerCamera
{
public:

	//		初期化処理
	virtual void Initialize() = 0;

	//		更新処理
	virtual void Update() = 0;

	//		終了処理
	virtual void Finalize() = 0;

	//		デストラクタ
	virtual ~IPlayerCamera() = default;
};