/*
* @file		ITutorialManager.h
* @brief	チュートリアルマネージャーのインターフェイス
* @author	Morita
* @date		2024/09/17
*/

#pragma once

class ITutorialManager
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
	virtual ~ITutorialManager() = default;
};
