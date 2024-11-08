/*
* @file		IAnimation
* @brief	アニメーションインターフェース
* @author	Morita
* @date		2024/08/25
*/

#pragma once

#include "pch.h"

#include "../Bones/BonInformation.h"

class IAnimation
{
public:

	//		初期化処理
	virtual void Initialize() = 0;

	/*
	*	更新処理
	*
	*	@param	(speed)		速度
	*	@param	(position)	座標
	*	@param	(angle)		角度
	*	@param	(height)	頭の高さ
	*	@param	(bonesInformation)	ボーンの情報
	*/
	virtual void Update(float speed, DirectX::SimpleMath::Vector3 position,
		DirectX::SimpleMath::Vector2 angle,
		float height, std::vector<PlayerBonsInformation>* bonesInformation) = 0;

	//		終了処理
	virtual void Finalize() = 0;

	//		デストラクタ
	virtual ~IAnimation() = default;
};