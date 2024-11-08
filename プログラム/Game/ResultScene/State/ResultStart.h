/*
* @file		ResultStart.h
* @brief	リザルト開始処理
* @author	Morita
* @date		2024/05/28
*/

#pragma once

#include "../ResultManager.h"

#include "../IResultManager.h"

class ResultManager;

class ResultStart : public IResultManager
{
public:

	/*
	*	コンストラクタ
	* 
	*	@param	(resultManager)	リザルトマネージャーのインスタンス
	*/
	ResultStart(ResultManager* resultManager);
	
	//		デストラクタ
	~ResultStart();

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