/*
* @file		IPlayer
* @brief	プレイヤーのインターフェイス
* @author	Morita
* @date		2024/04/03
*/

#pragma once

#include "pch.h"

class IPlayer
{
public:

	//		初期化処理
	virtual void Initialize() = 0;

	//		更新処理
	virtual void Update() = 0;

	//		移動処理
	virtual void Move() = 0;

	//		アニメーションの更新
	virtual void Animation() = 0;

	//		描画処理
	virtual void Render() = 0;

	//		終了処理
	virtual void Finalize() = 0;

	//		デストラクタ
	virtual ~IPlayer() = default;
};

