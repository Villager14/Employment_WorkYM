/*
* @file		IPostEffect.h
* @brief	ポストエフェクトのインターフェイス
* @author	Morita
* @date		2024/10/21
*/

#pragma once

#include "pch.h"

class IPostEffect
{
public:

	//		初期化処理
	virtual void Initialize() = 0;

	//		更新処理
	virtual void Update() = 0;

	//		オブジェクト描画
	virtual void ObjectRender() = 0;

	//		ポストエフェクト後の描画
	virtual void PostEffectRender() = 0;

	//		終了処理
	virtual void Filanize() = 0;

	//		テクスチャを受け取る
	virtual ID3D11ShaderResourceView* GetTexture() = 0;

	//		デストラクタ
	virtual ~IPostEffect() = default;

};