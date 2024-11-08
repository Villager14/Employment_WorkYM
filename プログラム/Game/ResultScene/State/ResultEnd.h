/*
* @file		ResultStay.cpp
* @brief	リザルト待機処理
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultEnd : public IResultManager
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(resultManager)	リザルトマネージャーのインスタンス
	*/
	ResultEnd(ResultManager* resultManager);
	
	//		デストラクタ
	~ResultEnd();

	//		初期化処理
	void Initialize() override;

	//		更新処理
	void Update() override;

	//		描画処理
	void Render() override;

	//		終了処理
	void Finalize() override;

private:

	//		リザルトマネージャー
	ResultManager* m_resultManager;

	//		時間
	float m_time;
};