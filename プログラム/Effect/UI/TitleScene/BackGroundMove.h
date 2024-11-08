/*
* @file		BackGroundMove.h
* @brief	背景の移動
* @author	Morita
* @date		2024/05/24
*/

#pragma once

#include "Library/Shader/UIRenderManager.h"

class BackGroundMove
{
public:

	//		コンストラクタ
	BackGroundMove();

	//		デストラクタ
	~BackGroundMove();

	//		初期化処理
	void Initialize();

	//		更新処理
	void Update();

	//		描画処理
	void Render();

	//		終了処理
	void Finalize();

public:

	//		コンストバッファ
	struct ConstBuffer
	{
		DirectX::SimpleMath::Vector4 windowSize;		//		ウィンドウサイズ
		DirectX::SimpleMath::Matrix  rotationMatrix;	//		回転行列
		DirectX::SimpleMath::Vector4 time;				//		時間
	};

private:

	//		背景の速度
	const float BACK_GROUND_SPEED = 0.1f;

private:

	//		UI描画マネージャー
	std::unique_ptr<UIRenderManager> m_uiRenderManager;

	//		時間
	float m_time;

	//		コンストバッファ
	ConstBuffer buffer;
};
