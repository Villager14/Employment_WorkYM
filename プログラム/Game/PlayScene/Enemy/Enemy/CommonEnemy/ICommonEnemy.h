/*
* @file		ICommonEnemy.h
* @brief	一般的な敵のインターフェイス
* @author	Morita
* @date		2024/05/01
*/

#pragma once

class ICommonEnemy
{
public:
	//		初期化処理
	virtual void Initialize() = 0;

	//		更新処理
	virtual void Update() = 0;

	//		描画処理
	virtual void Render() = 0;

	//		終了処理
	virtual void Finalize() = 0;

	//		デストラクタ
	virtual ~ICommonEnemy() = default;

};