/*
* @file		IFactory
* @brief	ファクトリーのインターフェイス
* @author	Morita
* @date		2024/08/21
*/

#pragma once

#include "pch.h"

#include "Game/PlayScene/ObjectManager/ObjectManager.h"

#include "Library/Mesh/ObjectMesh.h"

#include "Game/PlayScene/ObjectManager/ObjectInformation.h"

#include "Effect/PostEffect/PostEffectFlag.h"

#include "Factory.h"

#include "Effect/PostEffect/PostEffectObjectShader.h"

class IFactory
{
public:
	//		初期化処理
	virtual void Initialize(ObjectInformation information) = 0;

	//		更新処理
	virtual void Update() = 0;

	//		描画処理
	virtual void Render(PostEffectFlag::Flag flag,
		PostEffectObjectShader* postEffectObjectShader) = 0;

	//		終了処理
	virtual void Finalize() = 0;

	//		オブジェクトタイプ
	virtual Factory::Object GetObjectType() = 0;

	//		オブジェクトメッシュを受け取る
	virtual ObjectMesh* GetObjectMesh(int index) = 0;

	/*
	*	ポストエフェクトフラグ
	*
	*	@return インスタンスのポインタ
	*/
	virtual PostEffectFlag* GetPostEffectFlag() = 0;

	//		デストラクタ
	virtual ~IFactory() = default;
};
